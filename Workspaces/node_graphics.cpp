#include "node_graphics.h"


NodeGraphics::NodeGraphics() : shared_graphics(NodeGraphicsShared::get_instance())
{
	qDebug() << this << "NodeGraphics created";
	apply_settings();
}

NodeGraphics::~NodeGraphics()
{

}

QRectF NodeGraphics::boundingRect() const
{
	return QRectF(0, 0, shared_graphics->width, shared_graphics->height);
}

void NodeGraphics::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	shared_graphics->paint(painter);
	if (this->isSelected())
	{
		painter->setPen(shared_graphics->pen_selected);
	}
	else {
		painter->setPen(shared_graphics->pen_default);
	}
	painter->drawRoundedRect(boundingRect(), 20, 20);
}

void NodeGraphics::set_node_parent(Node* parent)
{
	parent_node = parent;
}

Node* NodeGraphics::get_node_parent() const
{
	return parent_node;
}

void NodeGraphics::apply_settings()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
}
