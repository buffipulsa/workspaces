#pragma once
#include "node.h"

#include <QObject>
#include <QList>


class NodeManager : public QObject
{
	Q_OBJECT

public:
	explicit NodeManager(QGraphicsScene* scene, QObject* parent = nullptr);
	~NodeManager();

	Node* create_node(const QPointF& position);
	void delete_node(Node* node);
	void delete_all_nodes();

	QList<Node*> get_all_nodes() const;

private:
	QGraphicsScene* scene;
	QList<Node*> nodes;
	mutable QMutex mutex;

	NodeManager(const NodeManager&) = delete;
	NodeManager& operator=(const NodeManager&) = delete;
};

