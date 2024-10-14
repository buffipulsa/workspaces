#include "create_port_data_node_command.h"
#include "port_data_node.h"

#include <maya/MGlobal.h>
#include <maya/MStatus.h>
#include <maya/MArgList.h>

void* CreatePortDataNodeCommand::creator()
{
	return new CreatePortDataNodeCommand();
}

MStatus CreatePortDataNodeCommand::doIt(const MArgList& args)
{
	if (args.length() != 1)
	{
		MGlobal::displayError("Invalid number of arguments. Usage: createPortNode <port>");
		return MS::kFailure;
	}

	int port = args.asInt(0);

	PortDataNode* node = static_cast<PortDataNode*>(PortDataNode::creator());
	if (!node) {
		MGlobal::displayError("Failed to create node.");
		return MS::kFailure;
	}

	node->setupTcpConnection(port);

	return MS::kSuccess;
}
