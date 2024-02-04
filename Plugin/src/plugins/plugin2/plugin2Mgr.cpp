#include "plugin2Mgr.h"
#include "extension/extension.h"
#include "plugin1/plugin1Mgr.h"
#include "plugin1/plugin1Test.h"
#include <QDebug>

Plugin2Mgr::Plugin2Mgr(QObject *parent) : QObject(parent)
{
    m_test = std::make_unique<Plugin2Test>();
    execPlugin1TestFunc();
}

void Plugin2Mgr::execPlugin1TestFunc()
{
    auto plugin1Mgr = Extension::instance()->getObject<Plugin1Mgr>();
    if(plugin1Mgr) {
        const auto& plugin1Test = plugin1Mgr->getPlugin1Test();
        qInfo() << "777777 plugin1 multir: " << __FUNCTION__ << plugin1Test->multi(3, 5);
    }
}

