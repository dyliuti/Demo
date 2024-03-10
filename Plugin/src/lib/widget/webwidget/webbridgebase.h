#ifndef WEB_BRIDGE_BASE_H
#define WEB_BRIDGE_BASE_H

#include <QObject>
#include "widget_global.h"

class WIDGET_EXPORT WebBridgeBase : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

signals:
    void sigClose();
};

#endif // WEB_BRIDGE_BASE_H
