#pragma once
#include "node_graphics_shared.h"

#include <QSharedPointer>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QPen>
#include <QColor>

class Node;

class NodeGraphics : public QGraphicsItem
{
public:
	NodeGraphics();
	~NodeGraphics();

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void set_node_parent(Node* parent);
	Node* get_node_parent() const;

private:
	QSharedPointer<NodeGraphicsShared> shared_graphics;
	Node* parent_node;

	void apply_settings();
};

