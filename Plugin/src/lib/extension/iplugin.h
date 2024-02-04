#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "define.h"
#include <QObject>

class EXTENSION_EXPORT IPlugin : public QObject
{
    Q_OBJECT
public:
    virtual bool load() = 0;
};

#endif // GOLANGASTPLUGIN_H
