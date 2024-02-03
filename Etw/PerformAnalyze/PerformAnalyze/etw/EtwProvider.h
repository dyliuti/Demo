#pragma once

#include <QEvent>
#include <QMap>
#include <QObject>
#include <QPointer>
#include <QString>
#include <list>

#ifdef Q_OS_WIN
#include <windows.h>
#include <evntrace.h>
#endif

enum EventType {
    EventType_EventTime = 0, // much time spend to handle event
    EventType_LowFps = 8 // low fps
};

typedef struct _OneEventHandleInfo {
    QString strObjectName;
    qint64 startHandleTimeMS = 0;
    qint64 spendTimeMS = 0;
    QEvent::Type type;
} OneEventHandleInfo;

typedef struct _OneTypeEventHandleInfo {
    QString lastObjClassName;
    qint64 spendTimeMS = 0;
    qint32 count = 0;
} OneTypeEventHandleInfo;

class EtwProvider {
public:
    static EtwProvider& instance();
    void init();
    void uninit();
    // handle events statistics
    void addOneEventHandleInfo(QPointer<QObject>& o, QEvent* e, qint64 startHandleTimeMS, qint64 spendTimeMS);
    QString getEventHandleStatistics(qint64 lastMS);

protected:
    EtwProvider() { init(); }
    ~EtwProvider() { uninit(); }

#if (defined Q_OS_WIN)
public:
    void logEtwEvent(EventType type, quint8 timems);

private:
    static ULONG WINAPI ControlCallback(WMIDPREQUESTCODE RequestCode, PVOID Context, ULONG* Reserved, PVOID Header);
    const GUID MyCategoryGuid = { 0x00000000, 0x1111, 0x1111, { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 } };
    const GUID ProviderGuid = { 0x00000000, 0x1111, 0x1111, { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 } };
    typedef struct _event {
        EVENT_TRACE_HEADER Header;
    } MY_EVENT, *PMY_EVENT;
    static TRACEHANDLE g_SessionHandle; // The handle to the session that enabled the provider.
    static ULONG g_EnableFlags; // Determines which class of events to log.
    static UCHAR g_EnableLevel; // Determines the severity of events to log.
    static BOOL g_TraceOn; // Used by the provider to determine whether it should log events.
#endif

    // collect UpdateRequest, MetaCall
    QMap<qint32 /*event type*/, QList<OneEventHandleInfo>> m_mapEventsHandleInfo;
    const qint32 cMaxEventInfoCount = 100;
    std::list<OneEventHandleInfo> m_listEventInfo;
};
