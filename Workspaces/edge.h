#pragma once

#include "enums.h"
#include "edge_graphics.h"

#include <QObject>


class Edge : public QObject
{
	Q_OBJECT

public:

	Edge(EdgeType type, QGraphicsItem* parent = nullptr);
	~Edge();

	EdgeGraphics* edge_graphics;

	void set_start_pos(const QPointF& pos);
	void set_end_pos(const QPointF& pos);
	void update_edge();

private:
	EdgeType type;
	QPointF start_pos;
	QPointF end_pos;
};

