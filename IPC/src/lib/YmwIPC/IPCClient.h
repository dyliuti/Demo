#ifndef IPCCLIENT_H
#define IPCCLIENT_H
#include "IPCBase.h"
#include <QObject>
#include <QTcpSocket>
#include <QDeadlineTimer>
#include <QThread>
#include "ymwIPC_global.h"
#include "IPCProtocol/IPCMessageType.h"

class QTcpSocket;
class YMWIPC_EXPORT IPCClient : public IPCBase
{
    Q_OBJECT

public:
    explicit IPCClient(qint64 serverPort, QObject *parent = nullptr);
    ~IPCClient();
    void run() override;

    void postMessageToServer(qint8 dataType, const QByteArray &data = "");
    QByteArray sendMessageToServer(qint8 dataType, const QByteArray &data = "", int timeout = REMOTE_CALL_TIMEOUT);

public slots:
    void onReadSocket();
    void onDiscardSocket();

private:
    QThread m_workThread;
    QTcpSocket* m_tcpsocket = nullptr;
};

#endif // IPCCLIENT_H
