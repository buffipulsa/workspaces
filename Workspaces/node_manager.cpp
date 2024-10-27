
#include "node_manager.h"
#include "graphics_scene.h"
#include "enums.h"

#include <QMutexLocker>


NodeManager::NodeManager(QGraphicsScene* scene, QObject* parent /*= nullptr*/)
	: QObject(parent), scene(scene)
{

}

NodeManager::~NodeManager()
{
	delete_all_nodes();
}

Node* NodeManager::create_node(const QPointF& position)
{
	QMutexLocker locker(&mutex);

	Node* node = new Node();
	node->set_position(position);

	scene->addItem(node->node_graphics);

	nodes.append(node);

	return node;
}

Edge* NodeManager::create_edge()
{
	QMutexLocker locker(&mutex);

	Edge* edge = new Edge(EdgeType::DIRECT);

	return edge;
}

void NodeManager::delete_node(Node* node)
{
	QMutexLocker locker(&mutex);

	if(node)
	{
		scene->removeItem(node->node_graphics);
		nodes.removeAll(node);
		delete node->node_graphics;
		delete node;
		node = nullptr;
	}
}

void NodeManager::delete_all_nodes()
{
	QMutexLocker locker(&mutex);

	for (Node* node : nodes)
	{
		scene->removeItem(node->node_graphics);
		delete node->node_graphics;
		delete node;
		node = nullptr;
	}

	nodes.clear();

}

QList<Node*> NodeManager::get_all_nodes() const
{
	QMutexLocker locker(&mutex);
	
	return nodes;
}
