#include "socket.h"
#include "socket_graphics.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>



Socket::Socket(SocketType type, QGraphicsItem* parent) 
	: type(type), socket_graphics(new SocketGraphics(type, parent))
{
	signals_slots();

}

Socket::~Socket()
{

}

QString Socket::get_type()
{
	if (type == SocketType::INPUT) {
		return "INPUT";
	}
	else {
		return "OUTPUT";
	}
}

void Socket::signals_slots()
{
	connect(socket_graphics, &SocketGraphics::signal_socket_clicked, this, &Socket::slot_socket_clicked);
	connect(socket_graphics, &SocketGraphics::signal_socket_released, this, &Socket::slot_socket_released);
	connect(socket_graphics, &SocketGraphics::signal_socket_drag_move, this, &Socket::slot_socket_drag_move);
	connect(socket_graphics, &SocketGraphics::signal_socket_enter_hovered, this, &Socket::slot_socket_enter_hovered);
	connect(socket_graphics, &SocketGraphics::signal_socket_leave_hovered, this, &Socket::slot_socket_leave_hovered);
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
}

void Socket::slot_socket_leave_hovered(SocketGraphics* socket)
{
	qDebug() << "Socket left hovered! Type: " << get_type();
}

