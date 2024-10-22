#pragma once

#include <QSharedPointer>
#include <QWeakPointer>
#include <QMutex>
#include <QPainter>
#include <QColor>
#include <QPen>


class SocketGraphicsShared
{
public:
	SocketGraphicsShared();
	~SocketGraphicsShared();

	SocketGraphicsShared(const SocketGraphicsShared&) = delete;
	SocketGraphicsShared& operator=(const SocketGraphicsShared&) = delete;

	static QSharedPointer<SocketGraphicsShared> get_instance();

	QColor input_background_color;
	QColor output_background_color;
	QColor hover_default_color;
	QPen hover_default_pen;

private:
	static QWeakPointer<SocketGraphicsShared> global_shared_node_graphics;
	static QMutex instance_mutex;
};

