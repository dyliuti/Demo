#include "ipcclientmgr.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>

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
//    QFile file("C:/Study/file.txt");
//    file.open(QIODevice::WriteOnly);
//    QDataStream out(&file);   // we will serialize the data into the file
//    out << message;   // serialize a string

    switch (dateType) {
    case PostTest_SC: {
        QByteArray data;
        bool flag;
        QDataStream stream(message);
        stream >> data;
        stream >> flag;

        qInfo() << "client recv data: " << QString::fromLocal8Bit(data) << flag;
        emit sigClientMsg(QString::fromLocal8Bit(data));

        QByteArray bytes;
        QDataStream dataStream(&bytes, QIODevice::WriteOnly);
        dataStream << QString("我收到数据了").toLocal8Bit();
        dataStream << true;

        qInfo() << bytes;
        IPCClientMgr::instance().postMessageToServer(PostTest_CS, bytes);
    }
    }
}
