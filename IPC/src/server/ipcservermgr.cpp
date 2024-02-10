#include "ipcservermgr.h"
#include <QDebug>
#include "IPCProtocol/IPCMessageType.h"
#include <QDataStream>

IPCServerMgr::IPCServerMgr(QObject *parent)
    : QObject{parent}
{
    m_ipcServer = new IPCServer(this);
    m_ipcServer->run();
    connect(m_ipcServer, &IPCServer::sigIpcDataReceived, this, &IPCServerMgr::onIPCDataReceived);
    connect(m_ipcServer, &IPCServer::sigNewConnect, [this](int descriptor) {
        emit sigNewConnect(descriptor);
    });
    connect(m_ipcServer, &IPCServer::sigDisconnect, [this]() {

    });
}

quint16 IPCServerMgr::serverPort()
{
    return m_ipcServer->serverPort();
}

void IPCServerMgr::onIPCDataReceived(qint8 dateType, const QByteArray &message)
{
    qInfo() << "111111: " << __FUNCTION__ << dateType << message;
    switch (dateType) {
    case PostTest_CS: {
        QByteArray data;
        bool flag;
        QDataStream stream(message);
        stream >> data;
        stream >> flag;
        emit sigNewMessage(QString::fromLocal8Bit(data));
        qInfo() << "sever recv data: " << QString(data) << flag;
    }
    }
}
