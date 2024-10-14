#pragma once

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QColor>

class Node : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	Node();
	~Node();

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
	int width;
	int height;
	int title_height;
	int edge_size;
	QColor background_color;

	QPen pen_default;
	QPen pen_selected;
};
