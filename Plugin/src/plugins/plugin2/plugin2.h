﻿#ifndef PLUGIN1_H
#define PLUGIN1_H

#include "extension/iplugin.h"

class Plugin2 : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.ymw.plugin" FILE "plugin2.json")

public:
    Plugin2();
    ~Plugin2();
    bool load() override;

private:
//    std::shared_ptr<LauncherxMgr> m_pMgr;
//    QPointer<Launcherx::LauncherxWidget> m_launcherXWidget;
};

#endif // PLUGIN1_H