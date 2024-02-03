#ifndef LAUNCHERX_PLUGIN_H
#define LAUNCHERX_PLUGIN_H

#include <extensionsystem/iplugin.h>
#include "LauncherxMgr.h"
#include <QElapsedTimer>
#include "view/LauncherxWidget.h"

class LauncherxPlugin : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.eeo.classin.plugin" FILE "launchx.json")

public:
    LauncherxPlugin();
    ~LauncherxPlugin();
    bool load() override;

private:
    void startupAnimation();

private:
    std::shared_ptr<LauncherxMgr> m_pMgr;
    QPointer<Launcherx::LauncherxWidget> m_launcherXWidget;
    QElapsedTimer m_timer;
};

#endif // LAUNCHERX_PLUGIN_H
