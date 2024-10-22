#include "socket_graphics_shared.h"

#include <QDebug>


QWeakPointer<SocketGraphicsShared> SocketGraphicsShared::global_shared_node_graphics;

QMutex SocketGraphicsShared::instance_mutex;

QSharedPointer<SocketGraphicsShared> SocketGraphicsShared::get_instance()
{
	QMutexLocker locker(&instance_mutex);

	QSharedPointer<SocketGraphicsShared> instance = global_shared_node_graphics.toStrongRef();

	if (instance.isNull())
	{
		instance = QSharedPointer<SocketGraphicsShared>(new SocketGraphicsShared());
		global_shared_node_graphics = instance;
	}

	return instance;
}

SocketGraphicsShared::SocketGraphicsShared()
{
	qDebug() << "SocketGraphicsShared created";

	input_background_color = QColor("#FF9900");
	output_background_color = QColor("#0066FF");
	hover_default_pen = QPen(QColor("#ff0000"), 2);
}

SocketGraphicsShared::~SocketGraphicsShared()
{
	qDebug() << "SocketGraphicsShared destroyed";
}
