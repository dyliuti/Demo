#include "IPCBase.h"
#include <QTcpSocket>
#include <QDataStream>

SendMsgCoordinator::SendMsgCoordinator()
{
    m_semaphore = new QSemaphore(0);
}

SendMsgCoordinator::~SendMsgCoordinator()
{
    delete m_semaphore;
}

IPCBase::IPCBase(QObject *parent)
    : QObject{parent}
{

}

void IPCBase::packMessage(QTcpSocket *socket, quint8 ipcType, quint8 messageType, const QByteArray &data)
{
    QByteArray packedMessage;
    QDataStream stream(&packedMessage, QIODevice::WriteOnly);

    // 写入消息类型和数据长度
    stream << ipcType;
    stream << messageType;
    stream << quint32(data.size());

    // 写入实际数据
    packedMessage.append(data);

    // 发送封装后的消息
    socket->write(packedMessage);
    socket->flush();
}

void IPCBase::packSendMessage(QTcpSocket *socket, quint8 ipcType, quint8 messageType, const QString &coordinatorId, const QByteArray &data)
{
    QByteArray packedMessage;
    QDataStream stream(&packedMessage, QIODevice::WriteOnly);
    stream << coordinatorId;
    stream << data;

    packMessage(socket, ipcType, messageType, packedMessage);
}

bool IPCBase::unpackMessage(const QByteArray &packedMessage, quint8 &ipcType, quint8 &messageType, QByteArray &data)
{
    QDataStream stream(packedMessage);

    // 读取消息类型和数据长度
    stream >> ipcType;
    stream >> messageType;
    quint32 dataSize;
    stream >> dataSize;

    // 确保有足够的数据可供读取
    if (stream.device()->bytesAvailable() < dataSize)
        return false;

    // 读取实际数据
    data = packedMessage.mid(stream.device()->pos(), dataSize);

    return true;
}



void IPCBase::readIPCData(QTcpSocket *socket)
{
    m_buffer.append(socket->readAll());

    while (!m_buffer.isEmpty()) {
        if (m_currentDataSize == -1 && m_buffer.size() >= getHeadSize()) {
            QDataStream stream(m_buffer);
            stream >> m_currentIPCType;
            stream >> m_currentMessageType;
            stream >> m_currentDataSize;
        }

        if (m_currentDataSize >= 0 && m_buffer.size() >= getCurPackTotalSize()) {
            // 有足够数据可以解包
            QByteArray packedMessage = m_buffer.left(getCurPackTotalSize());
            m_buffer.remove(0, packedMessage.size());

            // 解包数据
            quint8 ipcType;
            quint8 messageType;
            QByteArray data;
            if (unpackMessage(packedMessage, ipcType, messageType, data)) {
                // 处理解包后的消息
                if (ResultMessageIPC == ipcType) {
                    QString coordinatorId;
                    QByteArray realData;
                    QDataStream stream(data);
                    // 读取消息类型和数据长度
                    stream >> coordinatorId;
                    stream >> realData;

                    if (m_sendMsgCoordinator.contains(coordinatorId)) {
                        m_sendMsgCoordinator[coordinatorId]->m_remoteFunCallResult = realData;
                        m_sendMsgCoordinator[coordinatorId]->m_semaphore->release();
                    }
                } else if (SendMessageIPC == ipcType) {
                    QByteArray realData;
                    QDataStream stream(data);
                    // 读取消息类型和数据长度
                    stream >> m_coordinatorId;
                    stream >> realData;

                    emit sigIpcDataReceived(messageType, realData);
                } else {
                    emit sigIpcDataReceived(messageType, data);
                }
            }
            // 重置状态
            m_currentDataSize = -1;
        } else {
            break; // 等待更多数据到达
        }
    }
}

int IPCBase::getCurPackTotalSize()
{
    return m_currentDataSize + getHeadSize();
}

int IPCBase::getHeadSize()
{
    return sizeof(quint8) + sizeof(quint8) + sizeof(quint32);
}
