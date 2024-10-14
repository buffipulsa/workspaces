#pragma once

#include "ui_workspace.h"
#include "maya.h"
#include "graphics_view.h"

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QProcess>


class WorkSpace : public QWidget
{
	Q_OBJECT

public:
	WorkSpace(QWidget* parent);
	~WorkSpace();

private:
	Ui::WorkSpaceClass ui;

	Maya* maya_instance;
	
	QTcpServer* server;
	QTcpSocket* instance_socket;
	QTcpSocket* workspace_socket;

	GraphicsView* graphics_view;

	static int start_port;
	static int instance_port;
	static int workspace_port;

	int find_instance_port();
	int find_workspace_port();
	void start_workspace_server();
	void start_instance();
	void start_instance_connection_retry();
	void process_message(QByteArray* data);

private slots:
	void on_new_connection();
	void on_readyRead();
	void on_start_instance_btn_clicked();
	void on_instance_connected();
	void monitor_process_state_change(QProcess::ProcessState state);
	void on_pushButton_clicked();
};