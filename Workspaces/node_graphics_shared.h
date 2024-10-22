#pragma once
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMutex>
#include <QPainter>
#include <QColor>
#include <QPen>

class NodeGraphicsShared
{
public:
	NodeGraphicsShared();
	~NodeGraphicsShared();

	NodeGraphicsShared(const NodeGraphicsShared&) = delete;
	NodeGraphicsShared& operator=(const NodeGraphicsShared&) = delete;
	
	static QSharedPointer<NodeGraphicsShared> get_instance();

	void paint(QPainter* painter);

	int width;
	int height;
	int title_height;
	int edge_size;
	QPen pen_default;
	QPen pen_selected;

private:

	static QWeakPointer<NodeGraphicsShared> global_shared_node_graphics;
	static QMutex instance_mutex;

	QColor background_color;
};
