#include "qt_network_tools.h"

#include <QDebug>

#include <QTcpServer>
#include <QHostAddress>


int find_available_port(int start_port)
{
    while (start_port <= 65535) { // The maximum port number is 65535
        QTcpServer server;
        if (server.listen(QHostAddress::LocalHost, start_port)) {
            server.close();
            return start_port;
        }
        qDebug() << "Port:" << start_port << " is not available.";
        start_port++;
    }
    return -1;
}
