#ifndef PLUGIN2_MGR_H
#define PLUGIN2_MGR_H
#include <QObject>
#include "define.h"
#include "plugin2Test.h"

class PLUGIN2_EXPORT Plugin2Mgr : public QObject
{
    Q_OBJECT
public:
    Plugin2Mgr(QObject* parent = nullptr);
    const std::unique_ptr<Plugin2Test>& getPlugin2Test() {return m_test;}

    void execPlugin1TestFunc();

private:
    std::unique_ptr<Plugin2Test> m_test;
};

#endif // PLUGIN2_MGR_H
