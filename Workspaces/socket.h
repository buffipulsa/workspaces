#pragma once
#include "socket_graphics.h"
#include "enums.h"

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QRectF>


class Socket : public QObject
{
	Q_OBJECT

public:
	Socket(SocketType type, QGraphicsItem* parent = nullptr);
	~Socket();

	QString get_type() const;

private:
	QGraphicsItem* parent;
	SocketType type;
	SocketGraphics* socket_graphics;

	void connect_signals_slots();
	void set_position();

public slots:
	void slot_socket_clicked(SocketGraphics* socket);
	void slot_socket_released(SocketGraphics* socket);
	void slot_socket_drag_move(SocketGraphics* socket);
	void slot_socket_enter_hovered(SocketGraphics* socket);
	void slot_socket_leave_hovered(SocketGraphics* socket);
};


