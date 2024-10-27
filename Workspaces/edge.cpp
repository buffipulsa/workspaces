#include "edge.h"


Edge::Edge(EdgeType type, QGraphicsItem* parent)
	: type(type), edge_graphics(new EdgeGraphics(type, parent))
{

}

Edge::~Edge()
{

}

void Edge::set_start_pos(const QPointF& pos)
{
	start_pos = pos;
	edge_graphics->update();
}

void Edge::set_end_pos(const QPointF& pos)
{
	end_pos = pos;
	edge_graphics->update();
}

void Edge::update_edge()
{
	QPainterPath path;

	if (type == EdgeType::DIRECT)
	{
		path.moveTo(start_pos);
		path.lineTo(end_pos);
	}
	else if (type == EdgeType::BEZIER)
	{
		QPointF ctrl_start = QPointF((start_pos.x() + end_pos.x()) / 2, start_pos.y());
		QPointF ctrl_end = QPointF((start_pos.x() + end_pos.x()) / 2, end_pos.y());
		path.moveTo(start_pos);
		path.cubicTo(ctrl_start, ctrl_end, end_pos);
	}

	edge_graphics->setPath(path);
}
