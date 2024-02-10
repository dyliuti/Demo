#ifndef IPCSERVERMGR_H
#define IPCSERVERMGR_H

#include <QObject>
#include <IPCServer.h>
#include "mainwindow.h"

class IPCServerMgr : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(IPCServerMgr)
public:
    static IPCServerMgr &instance()
    {
        static IPCServerMgr self;
        return self;
    }

    void postMessageToClient(quint8 msgType, const QByteArray &data = "", int clientId = 0){m_ipcServer->postMessageToClient(msgType, data, clientId);}
    void returnMessageToClient(const QByteArray &data){m_ipcServer->returnMessageToClient(data);}
    quint16 serverPort();

signals:
    void sigNewConnect(int descriptor);
    void sigNewMessage(QString mes);

protected slots:
    void onIPCDataReceived(qint8 dateType, const QByteArray &message);

private:
    explicit IPCServerMgr(QObject *parent = nullptr);

protected:
    IPCServer * m_ipcServer = nullptr;
};

#endif // IPCSERVERMGR_H
