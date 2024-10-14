#pragma once
#include "enums.h"
#include <QGraphicsItem>


class SocketGraphics : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	SocketGraphics(SocketType type, QGraphicsItem* parent = nullptr);
	~SocketGraphics();

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

public:
	SocketType type;
	bool is_hovered;

signals:
	void signal_socket_clicked(SocketGraphics* socket);
	void signal_socket_released(SocketGraphics* socket);
	void signal_socket_drag_move(SocketGraphics* socket);
	void signal_socket_enter_hovered(SocketGraphics* socket);
	void signal_socket_leave_hovered(SocketGraphics* socket);
};

