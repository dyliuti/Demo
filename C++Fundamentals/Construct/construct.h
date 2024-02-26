#ifndef CONSTRUCT_H
#define CONSTRUCT_H
#include "test.h"
#include <QDebug>

class ConsTruct {
public:
    ConsTruct();
    void testReturnValue();
    void testEmplaceBack();
    void testSharedPtr();

private:
    int m_a = 0;
    Test* m_test {};
};

#endif // CONSTRUCT_H
