#pragma once

#include "graphics_scene.h"
#include "node_search_dialog.h"

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QPointF>
#include <QRectF>


class GraphicsView :public QGraphicsView
{
	Q_OBJECT

public:
	explicit GraphicsView(QWidget* parent = nullptr);
	~GraphicsView();

	GraphicsScene* graphics_scene;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;

private:
	void apply_settings();
	void draw_selection_rect();

	bool is_panning;
	bool is_dragging;
	QPoint pan_start;
	QPointF drag_start_pos;
	QRectF selection_rect;
	double zoom_factor;
	double min_zoom;
	double max_zoom;

	NodeSearchDialog* node_search_dialog;
};

