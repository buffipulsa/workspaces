#pragma once

#include "port_data_node.h"

#include <maya/MSceneMessage.h>
#include <maya/MGlobal.h>
#include <maya/MStatus.h>
#include <maya/MObject.h>
#include <maya/MFnNumericAttribute.h>
#include <ws2tcpip.h>

/*
Exit status = 0
New scene status = 1
Save scene status = 3
Save scene as status = 4
Export scene status = 5
Import scene status = 6
Export selected status = 7
Import selected status = 8
Export all status = 9
Import all status = 10
Export selected as status = 11
Import selected as status = 12
Export all as status = 13
Import all as status = 14
Export selected as reference status = 15
Import selected as reference status = 16
Export all as reference status = 17
Import all as reference status = 18
Export selected as reference options status = 19
Import selected as reference options status = 20
Export all as reference options status = 21
Import all as reference options status = 22
*/


const MTypeId PortDataNode::typeId = 0x138580;

PortDataNode::PortDataNode() : sockfd(INVALID_SOCKET) {}

PortDataNode::~PortDataNode() { closeSocket(); }

void* PortDataNode::creator()
{
    return new PortDataNode();
}

MStatus PortDataNode::initialize()
{
	return MS::kSuccess;
}

void PortDataNode::initializeWinSocket() 
{
	WSADATA wsaData;
	int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaResult != 0) {
		MGlobal::displayError("WSAStartup failed.");
		return;
	}
}

void PortDataNode::registerMayaCallbacks()
{
	MSceneMessage::addCallback(MSceneMessage::kMayaExiting, onMayaExit, this);
	MSceneMessage::addCallback(MSceneMessage::kBeforeSave, onMayaSaveScene, this);
}

void PortDataNode::onMayaExit(void* clientData)
{
	PortDataNode* node = static_cast<PortDataNode*>(clientData);
	if (node) {
		node->sendTcpMessage("0");
	}
}

void PortDataNode::onMayaSaveScene(void* clientData)
{
	PortDataNode* node = static_cast<PortDataNode*>(clientData);
	if (node) {
		node->sendTcpMessage("Maya saving the scene");
	}
}

void PortDataNode::setupTcpConnection(int port) 
{
	initializeWinSocket();
	// Create a TCP socket
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == INVALID_SOCKET) {
		MGlobal::displayError("Socket creation failed.");
		WSACleanup();
		return;
	}

	// Set the socket to non-blocking mode
	u_long nonBlocking = 1;
	if (ioctlsocket(sockfd, FIONBIO, &nonBlocking) != 0) {
		MGlobal::displayError("Failed to set socket to non-blocking mode.");
		closesocket(sockfd);
		WSACleanup();
		return;
	}

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); // Localhost

	// Connect to the server
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
		// Non-blocking sockets will return SOCKET_ERROR with WSAEWOULDBLOCK if the connection is in progress
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			MGlobal::displayError("TCP connection failed.");
			closesocket(sockfd);
			WSACleanup();
			return;
		}
	}

	// Send a message as soon as the connection is established
	sendTcpMessage("@@@@@@Maya connection established.@@@@@@");
	MGlobal::displayInfo("TCP connection established.");

	registerMayaCallbacks();
}

void PortDataNode::sendTcpMessage(const char* message)
{
	if (sockfd == INVALID_SOCKET) {
		MGlobal::displayError("No valid TCP connection.");
		return;
	}

	// Non-blocking send operation
	int result = send(sockfd, message, strlen(message), 0);
	if (result == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAEWOULDBLOCK) {
			MGlobal::displayError("Socket send operation would block, try again.");
		}
		else {
			MGlobal::displayError("Failed to send message.");
		}
		return;
	}

	MGlobal::displayInfo("TCP message sent.");
}

void PortDataNode::closeSocket()
{
	if (sockfd != INVALID_SOCKET) {
		closesocket(sockfd);
		WSACleanup();
		sockfd = INVALID_SOCKET;
	}
}

