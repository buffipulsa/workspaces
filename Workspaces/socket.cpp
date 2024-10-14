#include "socket.h"
#include "socket_graphics.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>



Socket::Socket(SocketType type, QGraphicsItem* parent) 
	: type(type), parent(parent), socket_graphics(new SocketGraphics(type, parent))
{
	connect_signals_slots();
	set_position();

}

Socket::~Socket()
{

}

QString Socket::get_type() const
{
	if (type == SocketType::INPUT) {
		return "INPUT";
	}
	else {
		return "OUTPUT";
	}
}

void Socket::connect_signals_slots()
{
	connect(socket_graphics, &SocketGraphics::signal_socket_clicked, this, &Socket::slot_socket_clicked);
	connect(socket_graphics, &SocketGraphics::signal_socket_released, this, &Socket::slot_socket_released);
	connect(socket_graphics, &SocketGraphics::signal_socket_drag_move, this, &Socket::slot_socket_drag_move);
	connect(socket_graphics, &SocketGraphics::signal_socket_enter_hovered, this, &Socket::slot_socket_enter_hovered);
	connect(socket_graphics, &SocketGraphics::signal_socket_leave_hovered, this, &Socket::slot_socket_leave_hovered);
}

void Socket::set_position()
{
	double height = parent->boundingRect().height() / 6;
	if (type == SocketType::INPUT)
		socket_graphics->setPos(-(socket_graphics->boundingRect().width() / 2), height);
	else
		socket_graphics->setPos(parent->boundingRect().width() - (socket_graphics->boundingRect().width() / 2), height);
}

void Socket::slot_socket_clicked(SocketGraphics* socket)
{
	qDebug() << "Socket clicked! Type: " << get_type();
}

void Socket::slot_socket_released(SocketGraphics* socket)
{
	qDebug() << "Socket released! Type: " << get_type();
}

void Socket::slot_socket_drag_move(SocketGraphics* socket)
{
	qDebug() << "Socket mouse drag! Type: " << get_type();
}

void Socket::slot_socket_enter_hovered(SocketGraphics* socket)
{
	qDebug() << "Socket enter hovered! Type: " << get_type();
	socket_graphics->set_hovered(true);
}

void Socket::slot_socket_leave_hovered(SocketGraphics* socket)
{
	qDebug() << "Socket left hovered! Type: " << get_type();
	socket_graphics->set_hovered(false);
}

