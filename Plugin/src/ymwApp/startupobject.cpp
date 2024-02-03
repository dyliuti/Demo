#include "startupobject.h"
#include "extension/pluginmanager.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QLoggingCategory>
#include <QSettings>
#include <QTextStream>
#include <QThreadPool>
#include <QTimer>
#include <QTranslator>
#include <QUrl>
#include <QVariant>
#include <QApplication>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTemporaryDir>
#include <QDesktopServices>
#include <QFileOpenEvent>

StartupObject::StartupObject(QObject *parent)
    : QObject(parent)
{}

void StartupObject::delayedInit()
{
    if (0 != initPluginManager()) {
        QCoreApplication::quit();
    }
}

void StartupObject::createAppDataDirectory()
{
    QString location = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir appDataDir;
    if (appDataDir.exists(location)) {
        if (appDataDir.mkpath(location)) {
            qInfo() << "mkpath failed" << location;
        }
    }
}

QString StartupObject::getPluginPaths()
{
    const QDir& rootDir = QApplication::applicationDirPath();
    const QString& rootDirPath = rootDir.canonicalPath();

    QString pluginPath;

#ifdef Q_OS_MAC
    pluginPath = rootDirPath + QLatin1String("/../Library/plugins");
#else
    pluginPath = rootDirPath + QLatin1String("/plugins");
#endif
    qInfo() << "777777: " << __FUNCTION__ << pluginPath;
    return pluginPath;
}

#include <QSettings>
//This function returns 0 if success
int StartupObject::initPluginManager()
{
    PluginManager::instance()->loadPlugins("com.ymw.plugin", getPluginPaths());

    return 0;
}
