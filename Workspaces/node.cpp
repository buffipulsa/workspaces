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
	: node_graphics(new NodeGraphics())
{
	setObjectName("Node class");

	node_graphics->set_node_parent(this);

	Socket* input = new Socket(SocketType::INPUT, node_graphics);
	Socket* output = new Socket(SocketType::OUTPUT, node_graphics);
}

Node::~Node() 
{
}

void Node::set_position(QPointF position)
{
	node_graphics->setPos(position);
}

