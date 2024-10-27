#pragma once
#include "enums.h"

#include <QGraphicsPathItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QWidget>

class EdgeGraphics : public QGraphicsPathItem
{
public:
	EdgeGraphics(EdgeType type, QGraphicsItem* parent = nullptr);
	~EdgeGraphics();

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	QRectF boundingRect() const override;

private:
	EdgeType type;
	QPointF start_pos;
	QPointF end_pos;
	QPen pen_default;
};

