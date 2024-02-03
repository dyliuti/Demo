#include "extension.h"

#include <QReadWriteLock>
#include <QDebug>

class Extension::impl
{
public:
    void addObject(QObject *obj)
    {
        QWriteLocker lock(&m_lock);
        if (obj == nullptr) {
            qWarning() << "Extension::addObject(): trying to add null object";
            return;
        }
        if (m_allObjects.contains(obj)) {
            qWarning() << "Extension::addObject(): trying to add duplicate object";
            return;
        }

        qDebug() << "Extension::addObject" << obj << obj->objectName();

        m_allObjects.append(obj);
    }

    void removeObject(QObject *obj)
    {
        if (obj == nullptr) {
            qWarning() << "Extension::removeObject(): trying to remove null object";
            return;
        }

        if (!m_allObjects.contains(obj)) {
            qWarning() << "Extension::removeObject(): object not in list:"
                       << obj << obj->objectName();
            return;
        }

        qDebug() << "Extension::removeObject" << obj << obj->objectName();

        QWriteLocker lock(&m_lock);
        m_allObjects.removeAll(obj);
    }

    QVector<QObject *> allObjects() { return m_allObjects; }

    QReadWriteLock *listLock() { return &m_lock; }

private:
    mutable QReadWriteLock m_lock;
    QVector<QObject *> m_allObjects;
};

Extension *Extension::instance()
{
    static Extension ext;
    return &ext;
}

Extension::Extension()
    : d(new impl)
{
}

Extension::~Extension()
{
}

void Extension::addObject(QObject *obj)
{
    return d->addObject(obj);
}

void Extension::removeObject(QObject *obj)
{
    d->removeObject(obj);
}

QVector<QObject *> Extension::allObjects()
{
    return d->allObjects();
}

QReadWriteLock *Extension::listLock()
{
    return d->listLock();
}
