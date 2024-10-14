#include "socket_graphics.h"

#include <QPainter>


SocketGraphics::SocketGraphics(SocketType type, QGraphicsItem* parent) 
	: QGraphicsItem(parent), type(type), is_hovered(false)
{
	qDebug() << "Socket graphics class parent: " << this->parentItem();
}

SocketGraphics::~SocketGraphics()
{

}

QRectF SocketGraphics::boundingRect() const
{
	return QRectF(0, 0, 15, 15);
}

void SocketGraphics::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qDebug() << "Painting socket";
	if (type == SocketType::INPUT) {
		painter->setBrush(QColor("#ff9900"));
	}
	else {
		painter->setBrush(QColor("#0066ff"));
	}
	if (is_hovered) {
		painter->setPen(QPen(QColor("#ff0000"), 2));
	}
	else
	{
		painter->setPen(Qt::NoPen);
	}
	painter->drawEllipse(boundingRect());

	return;
}

void SocketGraphics::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	emit signal_socket_clicked(this);

	update();

	QGraphicsItem::mousePressEvent(event);
}

void SocketGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	emit signal_socket_released(this);

	update();

	QGraphicsItem::mouseReleaseEvent(event);
}

void SocketGraphics::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
	emit signal_socket_drag_move(this);
	
	is_hovered = true;

	update();

	QGraphicsItem::dragMoveEvent(event);
}

void SocketGraphics::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	emit signal_socket_enter_hovered(this);

	is_hovered = true;

	update();

	QGraphicsItem::hoverEnterEvent(event);
}

void SocketGraphics::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	emit signal_socket_leave_hovered(this);

	is_hovered = false;

	update();

	QGraphicsItem::hoverLeaveEvent(event);
}
