#pragma once

#include <maya/MTypeId.h>
#include <maya/MPxNode.h>
#include <winsock2.h>

class PortDataNode : public MPxNode
{
public:
    static const MTypeId typeId;
 
	SOCKET sockfd;

    PortDataNode();
    virtual ~PortDataNode();
    static void* creator();
    static MStatus initialize();

	void setupTcpConnection(int port);

private:
	void initializeWinSocket();
	void registerMayaCallbacks();

	static void onMayaExit(void* clientData);
	static void onMayaSaveScene(void* clientData);

	void sendTcpMessage(const char* message);
	void closeSocket();
};