#ifndef STARTUPOBJECT_H
#define STARTUPOBJECT_H

#include <QObject>

class StartupObject : public QObject
{
    Q_OBJECT
public:
    explicit StartupObject(QObject *parent = 0);
    static int initPluginManager();
    static inline QString getPluginPaths();
    static void createAppDataDirectory();

signals:

public slots:
    void delayedInit();
};

#endif // STARTUPOBJECT_H
