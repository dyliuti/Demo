#ifndef EEOIPCBASE_H
#define EEOIPCBASE_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include <QSemaphore>
#include <memory>
#include "ymwIPC_global.h"

#define REMOTE_CALL_TIMEOUT 1000*1000

class QTcpSocket;

class SendMsgCoordinator
{
public:
    /*
    由于该类只是简单的做条件变量，所有暴漏了成员变量
该类后续理论上不允许添加太多的逻辑
*/
    QByteArray  m_remoteFunCallResult = "";
    QSemaphore  *m_semaphore;

    SendMsgCoordinator();
    ~SendMsgCoordinator();
};

typedef std::shared_ptr<SendMsgCoordinator> SendMsgCoordinatorPtr;

/*
 * 只负责进程间通信过程中拆包组包的功能
*/

class YMWIPC_EXPORT IPCBase : public QObject
{
    Q_OBJECT

public:
    enum IPCType {
        PostMessageIPC = 0,
        SendMessageIPC = 1,
        ResultMessageIPC = 2,
    };

    explicit IPCBase(QObject *parent = nullptr);
    virtual void run() {};

signals:
    void sigIpcDataReceived(quint8 dateType, const QByteArray &message);

protected:
    /*
     *
     *ipcType : SendDataIPC只是单纯的发送数据 RemoteFunCallIPC发送数据后，需要收到对端的响应
     *messageType: 这个是业务端需要关注的消息类型
     *
    */
    void packMessage(QTcpSocket *socket, quint8 ipcType, quint8 messageType, const QByteArray &data);
    bool unpackMessage(const QByteArray &packedMessage, quint8 &ipcType, quint8 &messageType, QByteArray &data);

    void packSendMessage(QTcpSocket *socket, quint8 ipcType, quint8 messageType,
                         const QString &coordinatorId, const QByteArray &data);

    void readIPCData(QTcpSocket* socket);

private:
    int getCurPackTotalSize();
    int getHeadSize();

protected:
    // 接收数据
    QByteArray  m_buffer;
    quint8      m_currentIPCType;
    quint8      m_currentMessageType;
    quint32     m_currentDataSize = -1;
    QString     m_coordinatorId = "";

    QMutex m_coordinatorMutex;
    QMap<QString, SendMsgCoordinatorPtr> m_sendMsgCoordinator;
};

#endif // EEOIPCBASE_H
