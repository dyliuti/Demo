#ifndef CONSTRUCT_H
#define CONSTRUCT_H
#include "test.h"
#include <QDebug>

class ConsTruct {
public:
    ConsTruct();
    void testReturnValue();
    void testEmplaceBack();

private:
    int m_a = 0;
};

#endif // CONSTRUCT_H
