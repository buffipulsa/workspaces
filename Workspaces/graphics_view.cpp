#include "graphics_view.h"
#include "graphics_scene.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPoint>
#include <QWheelEvent>
#include <QPointF>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QPaintEvent>



GraphicsView::GraphicsView(QWidget* parent) 
	: QGraphicsView(parent), is_panning(false), is_dragging(false), pan_start(QPoint(0, 0)), 
	drag_start_pos(QPointF(0, 0)), selection_rect(QRectF(0, 0, 0, 0)), 
	zoom_factor(1.2), min_zoom(0.1), max_zoom(5.0),
	graphics_scene(new GraphicsScene(this))
{
	this->setScene(graphics_scene);

	this->setDragMode(QGraphicsView::NoDrag);
	this->setCursor(Qt::ArrowCursor);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setRenderHint(QPainter::Antialiasing);
	this->setRenderHint(QPainter::TextAntialiasing);
	this->setRenderHint(QPainter::SmoothPixmapTransform);
	this->setCacheMode(QGraphicsView::CacheBackground);
	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

GraphicsView::~GraphicsView() {}

void GraphicsView::paintEvent(QPaintEvent* event)
{
	QGraphicsView::paintEvent(event);
	draw_selection_rect();
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MiddleButton) {
		is_panning = true;
		pan_start = event->pos();
		setCursor(Qt::ClosedHandCursor);
		event->accept();
	}
	else if (event->button() == Qt::LeftButton && event->modifiers() & Qt::ShiftModifier) {
		qDebug() << "Shift + Left button pressed.";
		is_dragging = true;
		drag_start_pos = mapToScene(event->pos());
		selection_rect = QRectF(drag_start_pos, drag_start_pos);
		this->update();
	}
	else {
		QGraphicsView::mousePressEvent(event);
	}

	return;
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	if (is_panning) {
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->pos().x() - pan_start.x()));
		verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->pos().y() - pan_start.y()));
		pan_start = event->pos();
		event->accept();
	}
	else if (is_dragging) {
		QPointF current_pos = mapToScene(event->pos());
		selection_rect = QRectF(drag_start_pos, current_pos).normalized();
		this->update();
	}
	else {
		QGraphicsView::mouseMoveEvent(event);
	}

	return;
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MiddleButton && is_panning) {
		is_panning = false;
		setCursor(Qt::ArrowCursor);
		event->accept();
	}
	else if (event->button() == Qt::LeftButton && event->modifiers() & Qt::ShiftModifier && is_dragging) {
		is_dragging = false;
		this->graphics_scene->clearSelection();

		QList<QGraphicsItem*> items = this->graphics_scene->items(selection_rect);

		for (QGraphicsItem* item : items) {
			item->setSelected(true);
		}

		selection_rect = QRectF(0, 0, 0, 0);
		this->update();
	}
	else {
		QGraphicsView::mouseReleaseEvent(event);
	}

	return;
}

void GraphicsView::wheelEvent(QWheelEvent* event)
{
	qreal zoom = this->transform().m11();

	QPointF old_scene_pos = mapToScene(event->position().toPoint());

	if (event->angleDelta().y() > 0)
	{
		if (zoom < max_zoom)
		{
			scale(zoom_factor, zoom_factor);
		}
	}
	else
	{
		if (zoom > min_zoom)
		{
			scale(1.0 / zoom_factor, 1.0 / zoom_factor);
		}
	}

	QPointF new_scene_pos = mapToScene(event->position().toPoint());

	QPointF delta = old_scene_pos - new_scene_pos;
	this->translate(delta.x(), delta.y());

	event->accept();

	return;
}

void GraphicsView::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_F)
	{
		QList<QGraphicsItem*> selected_items = this->scene()->selectedItems();

		if (!selected_items.isEmpty())
		{
			QRectF combined_rect;
			for (QGraphicsItem* item : selected_items) {
				QRectF item_rect = item->mapRectToScene(item->boundingRect());
				combined_rect = combined_rect.united(item_rect);
			}
			this->fitInView(combined_rect, Qt::KeepAspectRatio);
		}
		else {
			QRectF combined_rect;
			for (QGraphicsItem* item : graphics_scene->items()) {
				QRectF item_rect = item->mapRectToScene(item->boundingRect());
				combined_rect = combined_rect.united(item_rect);
			}
			this->fitInView(combined_rect, Qt::KeepAspectRatio);
		}
	}
	
	QGraphicsView::keyPressEvent(event);

	return;
}

void GraphicsView::draw_selection_rect()
{
	if (!selection_rect.isNull()) {
		QPointF top_left = mapFromScene(selection_rect.topLeft());
		QPointF bottom_right = mapFromScene(selection_rect.bottomRight());
		QRectF mapped_selection_rect = QRectF(top_left, bottom_right);
		
		QPainter painter(viewport());
		painter.setPen(QPen(Qt::white, 2, Qt::DashLine));
		painter.setBrush(QBrush(Qt::NoBrush));
		painter.drawRect(mapped_selection_rect);
	}

	return;
}
