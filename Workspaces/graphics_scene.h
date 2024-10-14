#pragma once

#include "node.h"
#include "socket.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QPointF>


class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit GraphicsScene(QObject* parent = nullptr);
	~GraphicsScene();

private:
	const static int size;

	QPointF get_viewport_center();

protected:
	void drawBackground(QPainter* painter, const QRectF& rect) override;

public slots:
	void add_node();
};


