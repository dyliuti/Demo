#include "MyApplication.h"
#include "etw/EtwProvider.h"
#include <QPointer>
#include <QDebug>
#include <QThread>
#include <QDateTime>

MyApplication::MyApplication(int &argc, char **argv) : QApplication(argc, argv)
{
    m_funcTimer.start();
}

bool MyApplication::notify(QObject* o, QEvent* e)
{
    qint64 startTime = m_funcTimer.elapsed();
    QPointer<QObject> guardObj(o);
//    qInfo() << "222222: " << o->objectName();
    bool bInMainThread = qApp->thread() == QThread::currentThread();
    if(bInMainThread && isEventNeed(e)) {
        EtwProvider::instance().addOneEventHandleInfo(guardObj, e, QDateTime::currentDateTime().toMSecsSinceEpoch(), m_funcTimer.elapsed() - startTime);
    }
    bool resEventNotify = QApplication::notify(o, e);
    qint64 spendTime = m_funcTimer.elapsed() - startTime;

    if (spendTime >= 100) {
        uchar timeMS = 0;
        if (spendTime > 2550) {
            timeMS = 255;
        } else {
            timeMS = spendTime / 10;
        }
        qInfo() << "notify 222222: " << spendTime << timeMS;
        EtwProvider::instance().logEtwEvent(EventType_EventTime, timeMS);
    }

    return resEventNotify;
}

bool MyApplication::isEventNeed(QEvent *e)
{
    if (e) {
        return (e->type() <= QEvent::HoverMove);
    }

    return false;
}
