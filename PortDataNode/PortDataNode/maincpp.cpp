#include "port_data_node.h"
#include "create_port_data_node_command.h"

#include <maya\MFnPlugin.h>
#include <maya\MGlobal.h>
#include <maya\MStatus.h>
#include <maya\MDrawRegistry.h>

MStatus initializePlugin(MObject obj)
{

	const char* vendor = "Einar Mar Magnusson";
#ifdef _DEBUG
	const char* version = "1.0.0 DEBUG";
#else
	const char* version = "1.0.0 DEBUG";
#endif
	const char* requiredAPIVersion = "Any";

	MStatus status;

	MFnPlugin fnPlugin(obj, vendor, version, requiredAPIVersion, &status); CHECK_MSTATUS_AND_RETURN_IT(status);
	
	status = fnPlugin.registerCommand("createPortDataNode", CreatePortDataNodeCommand::creator); CHECK_MSTATUS_AND_RETURN_IT(status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayError("Could not register the command: " + status.errorString());
		return MS::kFailure;
	}
	
	status = fnPlugin.registerNode("portDataNode", PortDataNode::typeId, PortDataNode::creator, PortDataNode::initialize); CHECK_MSTATUS_AND_RETURN_IT(status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayError("Could not register the node: " + status.errorString());
		return MS::kFailure;
	}

	return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;

	MFnPlugin fnPlugin(obj);

	status = fnPlugin.deregisterCommand("createPortNode"); CHECK_MSTATUS_AND_RETURN_IT(status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayError("Could not deregister the command: " + status.errorString());
		return MS::kFailure;
	}

	status = fnPlugin.deregisterNode(PortDataNode::typeId); CHECK_MSTATUS_AND_RETURN_IT(status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayError("Could not deregister the node: " + status.errorString());
		return MS::kFailure;
	}

	return MS::kSuccess;
}