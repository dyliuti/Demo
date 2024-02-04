#ifndef PLUGIN1_H
#define PLUGIN1_H

#include "extension/iplugin.h"
#include "plugin2Mgr.h"

class Plugin2 : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.ymw.plugin" FILE "plugin2.json")

public:
    Plugin2();
    ~Plugin2();
    bool load() override;

private:
    std::shared_ptr<Plugin2Mgr> m_pMgr;
};

#endif // PLUGIN1_H
