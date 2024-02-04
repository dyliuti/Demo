#ifndef PLUGIN1TEST_MGR_H
#define PLUGIN1TEST_MGR_H
#include <QObject>
#include "define.h"

class PLUGIN1_EXPORT Plugin1Test : public QObject
{
    Q_OBJECT
public:
    Plugin1Test();
    int multi(int a, int b) {return a*b;}

private:

};

#endif // PLUGIN1TEST_MGR_H
