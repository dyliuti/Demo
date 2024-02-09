#ifndef IPCMESSAGEHELPER_H
#define IPCMESSAGEHELPER_H

#include <QObject>
#include <set>
#include <map>
#include <QJsonObject>
#include "ymwIPC_global.h"

enum IPCDataType {
    PostTest_SC = 0,
    SendTest_SC = 1000,
    Unknow = 100000
};

class YMWIPC_EXPORT IPCMessageHelper : public QObject
{
    Q_OBJECT
public:
    explicit IPCMessageHelper(QObject *parent = nullptr);

    static QByteArray composeEnableUpload(bool enable, const std::set<quint64> &users);
    static void parseEnableUpload(const QByteArray &data, bool &enable, std::set<quint64> &users);

    static QByteArray composeDragToStage(quint64 uid, bool rejectDrop);
    static void parseDragToStage(const QByteArray &data, quint64 &uid, bool &rejectDrop);

    static QByteArray composeVideoWallTrack(bool isGroupPhoto, const QString &content);
    static void parseVideoWallTrack(const QByteArray &data, bool &isGroupPhoto, QString &content);

    static QByteArray composeLoginFirst(const QString &toolName, const QString &tipText);
    static void parseLoginFirst(const QByteArray &data, QString &toolName, QString &tipText);

    static QByteArray composeEquipmentStateChange(quint64 uid, bool state);
    static void parseEquipmentStateChange(const QByteArray &data, quint64 &uid, bool &state);

    static QByteArray composeOnLineStateChange(quint64 uid, bool onLineState);
    static void parseOnLineStateChange(const QByteArray &data, quint64 &uid, bool &onLineState);

    static QByteArray composeGroupUserChanged(int groupType, quint8 groupId, quint64 userId);
    static void parseGroupUserChanged(const QByteArray &data, int &groupTypeEnum, quint8 &groupId, quint64 &userId);

    static QByteArray composeQrcodeLurlResult(const QString &lurl, const QString &surl, int networkError, int errorNo, const QString &errorString);
    static void parseQrcodeLurlResult(const QByteArray &data, QString &lurl, QString &surl, int &networkError, int &errorNo, QString &errorString);

    static QByteArray composeQrcodeUploadPixmap(const QString &className, const QString &insitute, const QByteArray &img);
    static void parseQrcodeUploadPixmap(const QByteArray &data, QString &className, QString &insitute, QByteArray &img);

    static QByteArray composeSendLog(QtMsgType type, const QString &msg);
    static void parseSendLog(const QByteArray &data);

    static QByteArray composeInitCommand(quint64 uid);
    static void parseInitCommand(const QByteArray &data, quint64 &uid);

    static QByteArray composeGetConfig(const QString &key, const QString &defaultValue);
    static void parseGetConfig(const QByteArray &data, QString &key, QString &defaultValue);

    static QByteArray composeSetConfig(const QString &key, const QString &value);
    static void parseSetConfig(const QByteArray &data, QString &key, QString &value);

    static QByteArray composeRetransWebcamVideo(uint64_t cid, uint64_t uid, uint8_t channelId, const std::vector<uint32_t> &sequences);
    static void parseRetransWebcamVideo(const QByteArray &data, quint64 &cid, quint64 &uid, uint8_t &channelId, std::vector<uint32_t> &sequences);
};

#endif // IPCMessageHelper_H
