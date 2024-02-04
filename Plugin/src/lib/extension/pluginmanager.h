#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "define.h"
#include "pluginspec.h"
#include <QList>

class EXTENSION_EXPORT PluginManager : public QObject
{
    Q_OBJECT
signals:
    void loaded();

public:
    QList<Pluginspec *> pluginList();
    void loadPlugins(const char *iid, const QString &dir);
    bool isLoaded() const;

    QString path() const;

    static PluginManager *instance();

protected:
    PluginManager(QObject *parent = 0);
    virtual ~PluginManager();

private:
    class impl;
    const std::unique_ptr<impl> d;
};

#endif // PLUGINMANAGER_H
