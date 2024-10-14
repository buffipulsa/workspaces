#pragma once

#include <maya/MPxCommand.h>


class CreatePortDataNodeCommand : public MPxCommand 
{
public:
	static void* creator();
	MStatus doIt(const MArgList& args) override;
};

