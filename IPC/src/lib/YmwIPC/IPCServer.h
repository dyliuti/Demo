#ifndef IPCSERVER_H
#define IPCSERVER_H

#include <QObject>
#include "IPCBase.h"
#include "ymwIPC_global.h"

class QTcpServer;
class QTcpSocket;
/*
 * 只负责进程间通信过程中网络数据的接受和发送
*/
class YMWIPC_EXPORT IPCServer : public IPCBase
{
    Q_OBJECT

public:
    using IPCBase::IPCBase;
    void run() override;

    void postMessageToClient(quint8 msgType, const QByteArray &data = "", int clientId = 0);
    void returnMessageToClient(const QByteArray &data);
    quint16 serverPort();

signals:
    void sigNewConnect(int descriptor);
    void sigDisconnect();

private slots:
    void onNewConnection();
    void onHandleReadyRead();
    void onHandleClientDisconnected();

private:
    QTcpServer *m_server = nullptr;
    QMap<int, QTcpSocket *> m_socketMap;
};

#endif // IPCSERVER_H
