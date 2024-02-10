#ifndef IPCCLIENTMGR_H
#define IPCCLIENTMGR_H

#include <QObject>
#include <IPCClient.h>

class IPCClientMgr : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(IPCClientMgr)
public:
    static IPCClientMgr &instance()
    {
        static IPCClientMgr self;
        return self;
    }
    void postMessageToServer(qint8 dataType, const QByteArray &data = ""){m_ipcClient->postMessageToServer(dataType, data);}
    QByteArray sendMessageToServer(qint8 dataType, const QByteArray &data = "", int timeout = REMOTE_CALL_TIMEOUT){m_ipcClient->sendMessageToServer(dataType, data, timeout);}

    void init(qint64 serverPort);
    quint16 serverPort();

signals:
    void sigNewConnect(int descriptor);
    void sigClientMsg(QString msg);

protected slots:
    void onIPCDataReceived(qint8 dateType, const QByteArray &message);

private:
    explicit IPCClientMgr(QObject *parent = nullptr);

protected:
    IPCClient * m_ipcClient = nullptr;
};

#endif // IPCCLIENTMGR_H
