#include "node_graphics_shared.h"

#include <QDebug>


QWeakPointer<NodeGraphicsShared> NodeGraphicsShared::global_shared_node_graphics;

QMutex NodeGraphicsShared::instance_mutex;

QSharedPointer<NodeGraphicsShared> NodeGraphicsShared::get_instance()
{
	QMutexLocker locker(&instance_mutex);

	QSharedPointer<NodeGraphicsShared> instance = global_shared_node_graphics.toStrongRef();

	if (instance.isNull())
	{
		instance = QSharedPointer<NodeGraphicsShared>(new NodeGraphicsShared());
		global_shared_node_graphics = instance;
	}

	return instance;
}

NodeGraphicsShared::NodeGraphicsShared()
{
	qDebug() << "NodeGraphicsShared created";

	width = 180;
	height = 240;
	title_height = 24;
	edge_size = 10;
	background_color = QColor("#313131");

	pen_default = QPen(QColor("#7F000000"), 1);
	pen_selected = QPen(QColor("#FFFFA637"), 2);
}

NodeGraphicsShared::~NodeGraphicsShared()
{
	qDebug() << "NodeGraphicsShared destroyed";
}
