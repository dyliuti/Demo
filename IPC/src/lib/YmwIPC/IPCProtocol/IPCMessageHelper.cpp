#include "IPCMessageHelper.h"
#include <QDataStream>
#include <QDataStream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QIODevice>

IPCMessageHelper::IPCMessageHelper(QObject *parent)
    : QObject{parent}
{
}

QByteArray IPCMessageHelper::composeEnableUpload(bool enable, const std::set<quint64> &users)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << static_cast<quint32>(users.size()); // 写入 set 的元素数量
    for (quint64 number : users) {
        stream << number;                         // 逐个写入 set 中的值
    }
    stream << enable;

    return byteArray;
}

void IPCMessageHelper::parseEnableUpload(const QByteArray &data, bool &enable, std::set<quint64> &users)
{
    QDataStream stream(data);

    quint32 setSize;
    stream >> setSize; // 读取 set 的元素数量
    for (quint32 i = 0; i < setSize; ++i) {
        quint64 number;
        stream >> number; // 逐个读取 set 中的值
        users.insert(number);
    }

    stream >> enable;
}

QByteArray IPCMessageHelper::composeDragToStage(quint64 uid, bool rejectDrop)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << uid;
    stream << rejectDrop;

    return byteArray;
}

void IPCMessageHelper::parseDragToStage(const QByteArray &data, quint64 &uid, bool &rejectDrop)
{
    QDataStream stream(data);

    stream >> uid;
    stream >> rejectDrop;
}

QByteArray IPCMessageHelper::composeVideoWallTrack(bool isGroupPhoto, const QString &content)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << isGroupPhoto;
    stream << content;

    return byteArray;
}

void IPCMessageHelper::parseVideoWallTrack(const QByteArray &data, bool &isGroupPhoto, QString &content)
{
    QDataStream stream(data);

    stream >> isGroupPhoto;
    stream >> content;
}

QByteArray IPCMessageHelper::composeLoginFirst(const QString &toolName, const QString &tipText)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << toolName;
    stream << tipText;

    return byteArray;
}

void IPCMessageHelper::parseLoginFirst(const QByteArray &data, QString &toolName, QString &tipText)
{
    QDataStream stream(data);

    stream >> toolName;
    stream >> tipText;
}

QByteArray IPCMessageHelper::composeEquipmentStateChange(quint64 uid, bool state)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << uid;
    stream << state;
    return byteArray;
}

void IPCMessageHelper::parseEquipmentStateChange(const QByteArray &data, quint64 &uid, bool &state)
{
    QDataStream stream(data);
    stream >> uid;
    stream >> state;
}

QByteArray IPCMessageHelper::composeOnLineStateChange(quint64 uid, bool onLineState)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << uid; // 写入 set 的元素数量
    stream << onLineState;

    return byteArray;
}

void IPCMessageHelper::parseOnLineStateChange(const QByteArray &data, quint64 &uid, bool &onLineState)
{
    QDataStream stream(data);
    stream >> uid; // 读取 set 的元素数量
    stream >> onLineState;
}

QByteArray IPCMessageHelper::composeGroupUserChanged(int groupType, quint8 groupId, quint64 userId)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << groupType;
    stream << groupId;
    stream << userId;
    return byteArray;
}

void IPCMessageHelper::parseGroupUserChanged(const QByteArray &data, int &groupTypeEnum, quint8 &groupId, quint64 &userId)
{
    QDataStream stream(data);
    stream >> groupTypeEnum;
    stream >> groupId;
    stream >> userId;
}

QByteArray IPCMessageHelper::composeQrcodeLurlResult(const QString &lurl, const QString &surl, int networkError, int errorNo, const QString &errorString)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << lurl;
    stream << surl;
    stream << networkError;
    stream << errorNo;
    stream << errorString;
    return byteArray;
}

void IPCMessageHelper::parseQrcodeLurlResult(const QByteArray &data, QString &lurl, QString &surl, int &networkError, int &errorNo, QString &errorString)
{
    QDataStream stream(data);
    stream >> lurl;
    stream >> surl;
    stream >> networkError;
    stream >> errorNo;
    stream >> errorString;
}

QByteArray IPCMessageHelper::composeQrcodeUploadPixmap(const QString &className, const QString &insitute, const QByteArray &img)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << className;
    stream << insitute;
    stream << img;
    return byteArray;
}

void IPCMessageHelper::parseQrcodeUploadPixmap(const QByteArray &data, QString &className, QString &insitute, QByteArray &img)
{
    QDataStream stream(data);
    stream >> className;
    stream >> insitute;
    stream >> img;
}

QByteArray IPCMessageHelper::composeSendLog(QtMsgType type, const QString &msg)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << static_cast<int>(type);
    stream << msg;
    return byteArray;
}

void IPCMessageHelper::parseSendLog(const QByteArray &data)
{
    QtMsgType type;
    QString msg;
    QDataStream stream(data);
    int tmpValue = 0;
    stream >> tmpValue;
    type = static_cast<QtMsgType>(tmpValue);
    stream >> msg;
    if (type == QtInfoMsg) {
        qInfo() << msg;
    }
}

QByteArray IPCMessageHelper::composeInitCommand(quint64 uid)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << uid;
    return byteArray;
}

void IPCMessageHelper::parseInitCommand(const QByteArray &data, quint64 &uid)
{
    QDataStream stream(data);
    stream >> uid;
}

QByteArray IPCMessageHelper::composeGetConfig(const QString &key, const QString &defaultValue)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << key;
    stream << defaultValue;
    return byteArray;
}

void IPCMessageHelper::parseGetConfig(const QByteArray &data, QString &key, QString &defaultValue)
{
    QDataStream stream(data);
    stream >> key;
    stream >> defaultValue;
}

QByteArray IPCMessageHelper::composeSetConfig(const QString &key, const QString &value)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << key;
    stream << value;
    return byteArray;
}

void IPCMessageHelper::parseSetConfig(const QByteArray &data, QString &key, QString &value)
{
    QDataStream stream(data);
    stream >> key;
    stream >> value;
}

QByteArray IPCMessageHelper::composeRetransWebcamVideo(uint64_t cid, uint64_t uid, uint8_t channelId, const std::vector<uint32_t> &sequences)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << (quint64)cid;
    stream << (quint64)uid;
    stream << channelId;
    quint32 seqSize = sequences.size();
    stream << seqSize;
    for (size_t i = 0; i < seqSize; ++i) {
        stream << sequences[i];
    }
    return byteArray;
}

void IPCMessageHelper::parseRetransWebcamVideo(const QByteArray &data, quint64 &cid, quint64 &uid, uint8_t &channelId, std::vector<uint32_t> &sequences)
{
    QDataStream stream(data);
    stream >> cid;
    stream >> uid;
    stream >> channelId;

    quint32 sequenceSize = 0;
    stream >> sequenceSize;
    for (quint32 i = 0; i < sequenceSize; ++i) {
        uint32_t seq = 0;
        stream << seq;
        sequences.push_back(seq);
    }
}
