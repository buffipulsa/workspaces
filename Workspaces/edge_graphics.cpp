#include "edge_graphics.h"
#include "enums.h"


EdgeGraphics::EdgeGraphics(EdgeType type, QGraphicsItem* parent) 
	: type(type), QGraphicsPathItem(parent)
{
	this->setFlag(QGraphicsItem::ItemIsSelectable, true);
	this->setFlag(QGraphicsItem::ItemIsMovable, true);

	pen_default = QPen(Qt::red, 2);
	setPen(pen_default);
}

EdgeGraphics::~EdgeGraphics()
{

}

void EdgeGraphics::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QGraphicsPathItem::paint(painter, option, widget);

	painter->setRenderHint(QPainter::Antialiasing);

	if (type == EdgeType::DIRECT) {
		painter->drawLine(start_pos, end_pos);
	}
	else if (type == EdgeType::BEZIER) {
		QPainterPath path(start_pos);
		QPointF ctrl_start = QPointF((start_pos.x() + end_pos.x()) / 2, start_pos.y());
		QPointF ctrl_end = QPointF((start_pos.x() + end_pos.x()) / 2, end_pos.y());
		path.cubicTo(ctrl_start, ctrl_end, end_pos);
		painter->drawPath(path);
	}
}

QRectF EdgeGraphics::boundingRect() const
{
	return QRectF(start_pos, end_pos).normalized();
}
