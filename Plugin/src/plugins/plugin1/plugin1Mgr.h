#ifndef PLUGIN1_MGR_H
#define PLUGIN1_MGR_H
#include <QObject>
#include "define.h"
#include "plugin1Test.h"

class PLUGIN1_EXPORT Plugin1Mgr : public QObject
{
    Q_OBJECT
public:
    Plugin1Mgr(QObject* parent = nullptr);
    const std::unique_ptr<Plugin1Test>& getPlugin1Test() {return m_test;}

private:
    std::unique_ptr<Plugin1Test> m_test;
};

#endif // PLUGIN1_MGR_H
