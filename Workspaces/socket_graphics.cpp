#include "socket_graphics.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>


SocketGraphics::SocketGraphics(SocketType type, QGraphicsItem* parent) 
	: QGraphicsItem(parent), type(type), is_hovered(false), shared_graphics(SocketGraphicsShared::get_instance())
{
	apply_settings();
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
	if (type == SocketType::INPUT) {
		painter->setBrush(shared_graphics->input_background_color);
	}
	else {
		painter->setBrush(shared_graphics->output_background_color);
	}
	if (is_hovered) {
		painter->setPen(shared_graphics->hover_default_pen);
	}
	else
	{
		painter->setPen(Qt::NoPen);
	}
	painter->drawEllipse(boundingRect());

	return;
}

void SocketGraphics::set_hovered(bool hovered)
{
	is_hovered = hovered;

	update(); 
}

void SocketGraphics::apply_settings()
{
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptHoverEvents(true);
	setFlag(QGraphicsItem::ItemIsSelectable);
}

void SocketGraphics::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	event->accept();
	emit signal_socket_clicked(this);

	QGraphicsItem::mousePressEvent(event);
}

void SocketGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	emit signal_socket_released(this);

	QGraphicsItem::mouseReleaseEvent(event);
}

void SocketGraphics::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
	emit signal_socket_drag_move(this);

	QGraphicsItem::dragMoveEvent(event);
}

void SocketGraphics::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	emit signal_socket_enter_hovered(this);

	QGraphicsItem::hoverEnterEvent(event);
}

void SocketGraphics::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	emit signal_socket_leave_hovered(this);

	QGraphicsItem::hoverLeaveEvent(event);
}
