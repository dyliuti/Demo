#include "ipcclientmgr.h"
#include <QDebug>
#include <QDataStream>

IPCClientMgr::IPCClientMgr(QObject *parent)
    : QObject{parent}
{

}

void IPCClientMgr::init(qint64 serverPort)
{
    m_ipcClient = new IPCClient(serverPort, this);
    connect(m_ipcClient, &IPCClient::sigIpcDataReceived, this, &IPCClientMgr::onIPCDataReceived);
}

void IPCClientMgr::onIPCDataReceived(qint8 dateType, const QByteArray &message)
{
    qInfo() << "111111: " << __FUNCTION__ << dateType << message;
    emit sigClientMsg(message);
    switch (dateType) {
    case PostTest_SC: {
        QByteArray data;
        QDataStream stream(message);
        stream >> data;
        emit sigClientMsg(message);
    }
    }
}
