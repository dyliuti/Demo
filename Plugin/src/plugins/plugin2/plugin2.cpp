#include "plugin2.h"
#include "extension/extension.h"
//#include "extension/pluginmanager.h"


Plugin2::Plugin2()
{

}

Plugin2::~Plugin2()
{
}

bool Plugin2::load()
{
    m_pMgr = std::make_shared<Plugin2Mgr>(); // 不能放在构造函数中，不然plugin2Mgr构造函数中执行的plugin1Mgr执行不了
    Extension::instance()->addObject(m_pMgr.get());
    return true;
}

