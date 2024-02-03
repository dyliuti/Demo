#ifndef EXTENSION_H
#define EXTENSION_H

#include "ExtensionDefine.h"

#include <QVector>
#include <memory>
#include <QReadLocker>
#include <QObject>

class QObject;
class QReadWriteLock;

class EXTENSION_EXPORT Extension
{
public:
    static Extension *instance();

    void addObject(QObject *obj);
    void removeObject(QObject *obj);
    QVector<QObject *> allObjects();

    template<typename T>
    T *getObject()
    {
        QReadLocker lock(listLock());
        const QVector<QObject *> all = allObjects();
        for (QObject *obj : all) {
            if (T *result = qobject_cast<T *>(obj))
                return result;
        }
        return nullptr;
    }

    template<typename T, typename Predicate>
    T *getObject(Predicate predicate)
    {
        QReadLocker lock(listLock());
        const QVector<QObject *> all = allObjects();
        for (QObject *obj : all) {
            if (T *result = qobject_cast<T *>(obj))
                if (predicate(result))
                    return result;
        }
        return 0;
    }

protected:
    Extension();
    virtual ~Extension();

    QReadWriteLock *listLock();

private:
    class impl;
    std::unique_ptr<impl> d;
};

#endif
