#include "graphics_scene.h"
#include "node_manager.h"
#include "node.h"
#include "edge.h"
#include "socket.h"

#include <QGraphicsRectItem>
#include <QPainter>
#include <QRectF>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPointF>
#include <QGraphicsView>
#include <QPixmap>
#include <QLine>
#include <QVector>

#include <cmath>


const int GraphicsScene::size = 16000;

GraphicsScene::GraphicsScene(QObject* parent) 
	: QGraphicsScene(parent)
{
	node_manager = new NodeManager(this);
	setSceneRect(-size, -size, size, size);
}

GraphicsScene::~GraphicsScene() {}

QPointF GraphicsScene::get_viewport_center()
{
	QGraphicsView* view = views().first();
	QRectF view_rect = view->mapToScene(view->viewport()->rect()).boundingRect();
	QPointF center = view_rect.center();
	qDebug() << "Center: " << center;

	return center;
}

void GraphicsScene::drawBackground(QPainter* painter, const QRectF& rect)
{
	QGraphicsScene::drawBackground(painter, rect);

	int grid_size = 25;
	int grid_squares = 5;

	QColor background_color(69, 69, 69, 255);
	QColor grid_color_1(24, 24, 24);
	QColor grid_color_2(18, 18, 18, 255);

	QPen grid_pen_1(grid_color_1, 2);
	QPen grid_pen_2(grid_color_2, 1);

	painter->fillRect(rect, background_color);

	int left   = static_cast<int>(std::floor(rect.left()));
	int right  = static_cast<int>(std::ceil(rect.right()));
	int top    = static_cast<int>(std::floor(rect.top()));
	int bottom = static_cast<int>(std::ceil(rect.bottom()));

	int firstLeft = left - (left % grid_size);
	int firstTop = top - (top % grid_size);

	QVector<QLine> grid_lines_1, grid_lines_2;

	for (int x = firstLeft; x < right; x += grid_size) {
		if (x % (grid_size * grid_squares) == 0) {
			grid_lines_1.push_back(QLine(x, top, x, bottom));
		}
		else {
			grid_lines_2.push_back(QLine(x, top, x, bottom));
		}
	}

	for (int y = firstTop; y < bottom; y += grid_size) {
		if (y % (grid_size * grid_squares) == 0) {
			grid_lines_1.push_back(QLine(left, y, right, y));
		}
		else {
			grid_lines_2.push_back(QLine(left, y, right, y));
		}
	}

	painter->setPen(grid_pen_1);
	painter->drawLines(grid_lines_1);

	painter->setPen(grid_pen_2);
	painter->drawLines(grid_lines_2);

	return;
}

void GraphicsScene::add_node()
{
// 	Node* node = new Node();
// 	node->set_position(get_viewport_center());
// 	addItem(node->node_graphics);
	node_manager->create_node(get_viewport_center());
	update();

	return;
}
