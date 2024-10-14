#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QPointF>


class Edge : public QObject, public QGraphicsPathItem
{
	Q_OBJECT

public:
	enum class EdgeType { DIRECT, BEZIER };

	Edge(EdgeType type, QGraphicsItem* parent = nullptr);
	~Edge();

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	QRectF boundingRect() const override;

	void set_start_pos(const QPointF& pos);
	void set_end_pos(const QPointF& pos);
	void update_edge();

private:
	EdgeType type;
	QPointF start_pos;
	QPointF end_pos;
	QPen pen_default;
};

