#include "workspace.h"
#include "qt_network_tools.h"
#include "maya.h"
#include "graphics_view.h"

#include <QDebug>
#include <QByteArray>
#include <QHostAddress>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QTimer>
#include <QWidget>


int WorkSpace::start_port = 6000;
int WorkSpace::instance_port;
int WorkSpace::workspace_port;

WorkSpace::WorkSpace(QWidget *parent) : QWidget(parent), maya_instance(new Maya), server(new QTcpServer(this)), 
instance_socket(new QTcpSocket(this)), workspace_socket(NULL), graphics_view(new GraphicsView(this))
{
	ui.setupUi(this);
	
	ui.horizontalLayout->addWidget(graphics_view);

	instance_port = find_instance_port();
	workspace_port = find_workspace_port();

	ui.instance_port_lbl->setText(QString::number(instance_port));
	ui.workspace_port_lbl->setText(QString::number(workspace_port));

	start_workspace_server();
}

WorkSpace::~WorkSpace()
{
	delete maya_instance;
}

void WorkSpace::on_readyRead()
{
	if (workspace_socket->bytesAvailable()){
		QByteArray data = workspace_socket->readAll();
		qDebug() << "Data received:" << data;

		process_message(&data);
	}
	else {
		qDebug() << "No data available.";
	}

	return;
}

void WorkSpace::on_start_instance_btn_clicked()
{
	start_instance();

	return;
}

void WorkSpace::on_instance_connected()
{
	qDebug() << "Sending createPortDataNode command to Maya";
	instance_socket->write(QString("cmds.evalDeferred('cmds.createPortDataNode(%1)');").arg(workspace_port).toUtf8());

	return;
}

void WorkSpace::monitor_process_state_change(QProcess::ProcessState state)
{
	switch (state)
	{
	case QProcess::NotRunning:
		qDebug() << "State changed to not running!";
		ui.start_instance_btn->setStyleSheet("background-color: red");
		break;
	case QProcess::Starting:
		qDebug() << "State changed to starting!";
		ui.start_instance_btn->setStyleSheet("background-color: orange");
		break;
	case QProcess::Running:
		qDebug() << "State changed to running!";
		ui.start_instance_btn->setStyleSheet("background-color: green");
		break;
	default:
		break;
	}

	return;
}

void WorkSpace::on_pushButton_clicked()
{
	graphics_view->graphics_scene->add_node();
}

void WorkSpace::on_new_connection()
{
	workspace_socket = server->nextPendingConnection();
	if (workspace_socket) {
		qDebug() << "New connection established";

		connect(workspace_socket, &QTcpSocket::readyRead, this, &WorkSpace::on_readyRead, Qt::UniqueConnection);
		connect(workspace_socket, &QTcpSocket::disconnected, workspace_socket, &QTcpSocket::deleteLater, Qt::UniqueConnection);
		
		ui.workspace_port_lbl->setStyleSheet("QLabel { background-color : green; }");
	}
	else {
		qDebug() << "No pending connections available.";
		
		return;
	}

	return;
}

void WorkSpace::start_instance() 
{
	QtConcurrent::run([this]() {
		QMetaObject::invokeMethod(this, [this]() {
			maya_instance->start_maya_instance(&instance_port); 
		});

		if (instance_port == -1) {
			QMetaObject::invokeMethod(this, [this]() {
				qDebug() << "Failed to start instance on port: " << instance_port;
			});
			return;
		}

		QMetaObject::invokeMethod(this, [this]() {
			start_instance_connection_retry();
		});

	});

	connect(instance_socket, &QTcpSocket::connected, this, &WorkSpace::on_instance_connected, Qt::UniqueConnection);
	connect(maya_instance->maya_process, &QProcess::stateChanged, this, &WorkSpace::monitor_process_state_change, Qt::UniqueConnection);

	return;
}

void WorkSpace::start_instance_connection_retry()
{
	QTimer* retry_timer = new QTimer(this);
	connect(retry_timer, &QTimer::timeout, this, [this, retry_timer]() {
		qDebug() << "Attempting to connect to Maya instance on port:" << instance_port;

		instance_socket->connectToHost(QHostAddress::LocalHost, instance_port);

		if (instance_socket->waitForConnected(3000)) {
			qDebug() << "Socket connected to Maya instance on port:" << instance_port;

			retry_timer->stop();
			retry_timer->deleteLater();

			ui.instance_port_lbl->setStyleSheet("QLabel { background-color : green; }");
		}
		else {
			qDebug() << "Connection attempt failed, retrying...";
		}
	});

	retry_timer->start(5000);

	return;
}

void WorkSpace::process_message(QByteArray* data)
{
	QString message = QString::fromUtf8(*data);
	qDebug() << "Message: " << message;

	if (message == "0") {
		maya_instance->close_maya_instance();
		ui.instance_port_lbl->setStyleSheet("QLabel { background-color : red; }");
	}

	return;
}

int WorkSpace::find_instance_port()
{
	qDebug() << "Start port: " << start_port;

	instance_port = find_available_port(start_port);
	qDebug() << "Port: " << instance_port;

	if (instance_port == -1) {
		qDebug() << "Failed to find available instance port.";
		return -1;
	}
	return instance_port;
}

int WorkSpace::find_workspace_port()
{
	workspace_port = find_available_port(instance_port + 1);
	qDebug() << "Workspace port: " << workspace_port;

	if (workspace_port == -1) {
		qDebug() << "Failed to find available workspace port.";
		return -1;
	}
	return workspace_port;
}

void WorkSpace::start_workspace_server()
{
	server->listen(QHostAddress::LocalHost, workspace_port);
	if (!server->isListening()) {
		if (!server->listen(QHostAddress::LocalHost, workspace_port)) {
			qDebug() << "Failed to start the server: " << server->errorString();
		}
		else {
			qDebug() << "Server started listening on port" << workspace_port;
		}
	}
	else {
		qDebug() << "Server is already listening on port" << server->serverPort();
	}

	connect(server, &QTcpServer::newConnection, this, &WorkSpace::on_new_connection, Qt::UniqueConnection);

	return;
}





