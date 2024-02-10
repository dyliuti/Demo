#include "IPCServer.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

void IPCServer::run()
{
    m_server = new QTcpServer();
    // 7733
    if(m_server->listen(QHostAddress::Any, 7733)) {
        qInfo() << "IPCServer listen";
        connect(m_server, &QTcpServer::newConnection, this, &IPCServer::onNewConnection);
    } else {
        qInfo() << "IPCServer listen error";
    }
}

void IPCServer:: postMessageToClient(quint8 msgType, const QByteArray &data, int clientId)
{
    QObject obj;
    connect(&obj, &QObject::destroyed, this, [this, data, msgType, clientId]() {
        foreach (auto socket, m_socketMap) {
            if (socket->isOpen()) {
                if (clientId == 0 || clientId == socket->socketDescriptor()) {
                    packMessage(socket, PostMessageIPC, msgType, data);
                }
            } else {
                qInfo() << "IPCServer QTcpSocket is close " ;
            }
        }
    });
}

void IPCServer::returnMessageToClient(const QByteArray &data)
{
    QObject obj;
    connect(&obj, &QObject::destroyed, this, [this, data]() {
        foreach (auto socket, m_socketMap) {
            if (socket->isOpen()) {
                packSendMessage(socket, ResultMessageIPC, 0, m_coordinatorId, data);
                m_coordinatorId = "";
            } else {
                qInfo() << "IPCServer QTcpSocket is close " ;
            }
        }
    });
}

quint16 IPCServer::serverPort()
{
    return m_server->serverPort();
}

void IPCServer::onNewConnection()
{
    if (m_server->hasPendingConnections()) {
        qInfo() << "IPCServer sigNewConnect";
        QTcpSocket *socket = m_server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &IPCServer::onHandleReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &IPCServer::onHandleClientDisconnected);
        m_socketMap[socket->socketDescriptor()] = socket;
        emit sigNewConnect(socket->socketDescriptor());
    }
}

void IPCServer::onHandleReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        readIPCData(socket);
    }
}

void IPCServer::onHandleClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        for (auto it = m_socketMap.begin(); it != m_socketMap.end(); ++it) {
            if (it.value() == socket) {
                m_socketMap.remove(it.key());
                break;
            }
        }
        socket->deleteLater();
    }
    emit sigDisconnect();
}
