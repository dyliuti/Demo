#include "plugin1.h"
#include "extension/extension.h"
//#include "extension/pluginmanager.h"


Plugin1::Plugin1()
{

}

Plugin1::~Plugin1()
{
}

bool Plugin1::load()
{
    m_pMgr = std::make_shared<Plugin1Mgr>();
    Extension::instance()->addObject(m_pMgr.get());
    return true;
}

