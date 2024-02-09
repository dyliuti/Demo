#include "IPCClient.h"
#include <QThread>
#include <QEventLoop>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDataStream>
#include <QUuid>

IPCClient::IPCClient(qint64 serverPort, QObject *parent)
    :IPCBase{parent}
{
    m_tcpsocket = new QTcpSocket(this);
    connect(m_tcpsocket, &QTcpSocket::readyRead, this, &IPCClient::onReadSocket);
    connect(m_tcpsocket, &QTcpSocket::disconnected, this, &IPCClient::onDiscardSocket);

    m_tcpsocket->connectToHost(QHostAddress::LocalHost, serverPort);

    if(m_tcpsocket->waitForConnected()) {
        qDebug() << "EeoTcpServer::sendData ======= succ";
    } else {
        qDebug() << "EeoTcpServer::sendData ======= ccc";
    }

//    moveToThread(&m_workThread);
//    m_workThread.start();
}

IPCClient::~IPCClient()
{
    if (m_tcpsocket && m_tcpsocket->isOpen()) {
        m_tcpsocket->close();
    }
}

void IPCClient::run()
{

}

void IPCClient::postMessageToServer(qint8 dateType, const QByteArray &data)
{
    QObject obj;
    connect(&obj, &QObject::destroyed, this, [this, dateType, data](){
        packMessage(m_tcpsocket, PostMessageIPC, (qint8)dateType, data);
    });
}

QByteArray IPCClient::sendMessageToServer(qint8 dateType, const QByteArray &data, int timeout)
{
    QString coordinatorId = QUuid::createUuid().toString();

    {
        QMutexLocker mutexLocker(&m_coordinatorMutex);
        m_sendMsgCoordinator.insert(coordinatorId, std::make_shared<SendMsgCoordinator>());
    }

    {
        QObject obj;
        connect(&obj, &QObject::destroyed, this, [this, coordinatorId, dateType, data](){
            packSendMessage(m_tcpsocket, SendMessageIPC, (qint8)dateType, coordinatorId, data);
        });
    }

    QByteArray result;
    if (m_sendMsgCoordinator[coordinatorId]->m_semaphore->tryAcquire(1, timeout)) {
        result = m_sendMsgCoordinator[coordinatorId]->m_remoteFunCallResult;
    } else {
        qInfo() << " remote call faile ";
    }

    m_sendMsgCoordinator.remove(coordinatorId);
    return result;
}

void IPCClient::onReadSocket()
{
    readIPCData(m_tcpsocket);
}

void IPCClient::onDiscardSocket()
{
    qDebug() << "onDiscardSocket";
    m_tcpsocket->deleteLater();
    m_tcpsocket = nullptr;
}
