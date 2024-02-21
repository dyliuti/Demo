#ifndef TEST_H
#define TEST_H
#include <QDebug>

class Test {
public:
    Test(int a)
        : m_a(a)
    {
        qInfo() << "construct";
    };
    Test(const Test& a)
    {
        m_a = a.m_a;
        qInfo() << "left value copy construct";
    }
    Test(Test&& a)
    {
        m_a = a.m_a;
        qInfo() << "right value copy construct";
    }

    void operator=(const Test& a)
    {
        m_a = a.m_a;
        qInfo() << "left value copy assignment construct";
    }

    void operator=(Test&& a)
    {
        m_a = a.m_a;
        qInfo() << "right value move assignment construct";
    }
    void print() const { qInfo() << m_a; }

private:
    int m_a = 0;
};

#endif // TEST_H
