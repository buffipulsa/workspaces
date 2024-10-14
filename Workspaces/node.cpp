#include "node.h"
#include "socket.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QPen>
#include <QBrush>
#include <QColor>


Node::Node()
{
	setObjectName("Node class");

	width = 180;
	height = 240;
	title_height = 24;
	edge_size = 10;
	background_color = QColor("#313131");

	pen_default = QPen(QColor("#7F000000"), 1);
	pen_selected = QPen(QColor("#FFFFA637"), 2);

	this->setFlag(QGraphicsItem::ItemIsMovable);
	this->setFlag(QGraphicsItem::ItemIsSelectable);

	Socket* input = new Socket(SocketType::INPUT, this);
	Socket* output = new Socket(SocketType::OUTPUT, this);
}

Node::~Node() {}

QRectF Node::boundingRect() const
{
	return QRectF(0, 0, width, height);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setBrush(background_color);
	if (this->isSelected())
	{
		painter->setPen(pen_selected);
	} else {
		painter->setPen(pen_default);
	}
	painter->drawRoundedRect(boundingRect(), 20, 20);
}

