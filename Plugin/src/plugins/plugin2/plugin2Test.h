#ifndef PLUGIN2_TEST_H
#define PLUGIN2_TEST_H
#include <QObject>
#include "define.h"

class PLUGIN2_EXPORT Plugin2Test : public QObject
{
    Q_OBJECT
public:
    Plugin2Test();
    int add(int a, int b) {return a+b;}

private:

};

#endif // PLUGIN2_MGR_H
