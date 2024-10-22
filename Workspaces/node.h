#pragma once
#include "node_graphics.h"

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QColor>

class Node : public QObject
{
public:
	Node();
	~Node();

	void set_position(QPointF position);

	NodeGraphics* node_graphics;
};


