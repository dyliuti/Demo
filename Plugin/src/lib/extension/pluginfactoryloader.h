#ifndef PLUGINFACTORYLOADER_H
#define PLUGINFACTORYLOADER_H

#include "ExtensionDefine.h"
#include "pluginspec.h"

#include <QObject>
#include <memory>

class EXTENSION_EXPORT PluginFactoryLoader : public QObject
{
    Q_OBJECT
public:
    PluginFactoryLoader(const char *iid,
                        const QString &suffix = QString(),
                        Qt::CaseSensitivity cs = Qt::CaseSensitive);

    ~PluginFactoryLoader();

    void load();

    QList<Pluginspec *> pluginList();

protected:
    QObject *load(Pluginspec *spec);

    virtual void preload(Pluginspec *spec) = 0;

private:
    class impl;
    std::unique_ptr<impl> d;
};

#endif
