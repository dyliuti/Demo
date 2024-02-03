#include "EtwProvider.h"
#include <QDateTime>
#include <QDebug>
#include <QMetaEnum>
#if (defined Q_OS_WIN)
#pragma comment(lib, "Advapi32.lib")

TRACEHANDLE EtwProvider::g_SessionHandle = 0;
ULONG EtwProvider::g_EnableFlags = 0;
UCHAR EtwProvider::g_EnableLevel = 0;
BOOL EtwProvider::g_TraceOn = 0;

void EtwProvider::logEtwEvent(EventType type, quint8 timems)
{
    qInfo() << "333333 begin";
    if (g_TraceOn && g_SessionHandle && (0 == g_EnableLevel || TRACE_LEVEL_ERROR <= g_EnableLevel)) {
        qInfo() << "333333 enter";
        ULONG status = ERROR_SUCCESS;
        MY_EVENT MyEvent;
        // Initialize the event data structure.
        ZeroMemory(&MyEvent, sizeof(MY_EVENT));
        MyEvent.Header.Size = sizeof(EVENT_TRACE_HEADER);
        MyEvent.Header.Flags = WNODE_FLAG_TRACED_GUID | WNODE_FLAG_USE_MOF_PTR;
        MyEvent.Header.Guid = MyCategoryGuid;
        MyEvent.Header.Class.Type = type;
        MyEvent.Header.Class.Version = 1;
        MyEvent.Header.Class.Level = timems;
        status = TraceEvent(g_SessionHandle, &(MyEvent.Header));
    }
}

ULONG WINAPI EtwProvider::ControlCallback(WMIDPREQUESTCODE RequestCode, PVOID Context, ULONG* Reserved, PVOID Header)
{
    UNREFERENCED_PARAMETER(Context);
    UNREFERENCED_PARAMETER(Reserved);
    ULONG status = ERROR_SUCCESS;
    TRACEHANDLE TempSessionHandle = 0;
    switch (RequestCode) {
    case WMI_ENABLE_EVENTS: // Enable the provider.
    {
        qInfo() << "333333 WMI_ENABLE_EVENTS";
        SetLastError(0);
        // If the provider is already enabled to a provider, ignore
        // the request. Get the session handle of the enabling session.
        // You need the session handle to call the TraceEvent function.
        // The session could be enabling the provider or it could be
        // updating the level and enable flags.
        TempSessionHandle = GetTraceLoggerHandle(Header);
        if (INVALID_HANDLE_VALUE == (HANDLE)TempSessionHandle) {
            break;
        }

        if (0 == g_SessionHandle) {
            g_SessionHandle = TempSessionHandle;
        } else if (g_SessionHandle != TempSessionHandle) {
            break;
        }

        // Get the severity level of the events that the
        // session wants you to log.

        g_EnableLevel = GetTraceEnableLevel(g_SessionHandle);
        if (0 == g_EnableLevel) {
            // If zero, determine whether the session passed zero
            // or an error occurred.

            if (ERROR_SUCCESS == (status = GetLastError())) {
                // Decide what a zero enable level means to your provider.
                // For this example, it means log all events.
                ;
            } else {
                break;
            }
        }

        // Get the enable flags that indicate the events that the
        // session wants you to log. The provider determines the
        // flags values. How it articulates the flag values and
        // meanings to perspective sessions is up to it.

        g_EnableFlags = GetTraceEnableFlags(g_SessionHandle);
        if (0 == g_EnableFlags) {
            // If zero, determine whether the session passed zero
            // or an error occurred.

            if (ERROR_SUCCESS == (status = GetLastError())) {
                // Decide what a zero enable flags value means to your provider.
                ;
            } else {
                break;
            }
        }

        g_TraceOn = TRUE;
        break;
    }

    case WMI_DISABLE_EVENTS: // Disable the provider.
    {
        // Disable the provider only if the request is coming from the
        // session that enabled the provider.
        qInfo() << "333333 WMI_DISABLE_EVENTS";
        TempSessionHandle = GetTraceLoggerHandle(Header);
        if (INVALID_HANDLE_VALUE == (HANDLE)TempSessionHandle) {
            break;
        }

        if (g_SessionHandle == TempSessionHandle) {
            g_TraceOn = FALSE;
            g_SessionHandle = 0;
        }
        break;
    }

    default: {
        qInfo() << "333333 ERROR_INVALID_PARAMETER";
        status = ERROR_INVALID_PARAMETER;
        break;
    }
    }

    return status;
}
#endif

EtwProvider& EtwProvider::instance()
{
    static EtwProvider sInstance;
    return sInstance;
}

void EtwProvider::init()
{
#if (defined Q_OS_WIN)
    ULONG status = ERROR_SUCCESS;
    TRACEHANDLE RegistrationHandle = 0;
    TRACE_GUID_REGISTRATION EventClassGuids[] = {
        (LPGUID)&MyCategoryGuid, NULL
    };
    // Register the provider and specify the control callback function
    // that receives the enable/disable notifications.
    status = RegisterTraceGuids(
        (WMIDPREQUEST)EtwProvider::ControlCallback,
        NULL,
        (LPGUID)&ProviderGuid,
        sizeof(EventClassGuids) / sizeof(TRACE_GUID_REGISTRATION),
        EventClassGuids,
        NULL,
        NULL,
        &RegistrationHandle);
#endif
}

void EtwProvider::uninit()
{
#if (defined Q_OS_WIN)
    if (g_SessionHandle) {
        UnregisterTraceGuids(g_SessionHandle);
    }
#endif
}

void EtwProvider::addOneEventHandleInfo(QPointer<QObject>& o, QEvent* e, qint64 startHandleTime, qint64 spendTime)
{
    if (o && e) {
        OneEventHandleInfo info;
        info.strObjectName = o->metaObject()->className();
        info.spendTimeMS = spendTime;
        info.startHandleTimeMS = startHandleTime;
        info.type = e->type();
        if (m_listEventInfo.size() >= cMaxEventInfoCount) {
            m_listEventInfo.erase(m_listEventInfo.begin());
        }
        m_listEventInfo.push_back(info);
    }
}

typedef struct _EventHandleKey {
    QString className;
    QEvent::Type type;
    bool operator<(const _EventHandleKey& other) const
    {
        if (type != other.type) {
            return type < other.type;
        }
        return className < other.className;
    }
} EventHandleKey;

QString EtwProvider::getEventHandleStatistics(qint64)
{
    QString str;
    EventHandleKey key;
    qint32 maxValue = 0;
    QMap<EventHandleKey, qint32> mapEventHandleInfo;
    QMultiMap<qint32, EventHandleKey> mapEventSpendTimeInfo;

    for (std::list<OneEventHandleInfo>::const_iterator it = m_listEventInfo.cbegin(); it != m_listEventInfo.cend(); ++it) {
        mapEventHandleInfo[{ it->strObjectName, it->type }] += it->spendTimeMS;
    }

    for (QMap<EventHandleKey, qint32>::const_iterator it = mapEventHandleInfo.cbegin(); it != mapEventHandleInfo.cend(); ++it) {
        if (maxValue < it.value()) {
            maxValue = it.value();
            key = it.key();
        }
        mapEventSpendTimeInfo.insert(it.value(), it.key());
    }
    int eventEnumIndex = QEvent::staticMetaObject.indexOfEnumerator("Type");
    QString strEventTypeName = QEvent::staticMetaObject.enumerator(eventEnumIndex).valueToKey(key.type);
    if (strEventTypeName.isEmpty()) {
        strEventTypeName = QString::number(key.type);
    }
    str += key.className;
    str += " handle event:";
    str += strEventTypeName;
    str += " spend ";
    str += QString::number(maxValue);
    str += " ms";
    //     for (QMap<qint32, EventHandleKey>::const_iterator it = mapEventSpendTimeInfo.cbegin(); it != mapEventSpendTimeInfo.cend(); ++it) {
    //         qDebug() << "[dddd] event:" << it.value().type << " class name:" << it.value().className << " total spend time:" << it.key();
    //     }

    return str;
}
