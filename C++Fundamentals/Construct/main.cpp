#include "construct.h"
#include "test.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

/***
对象不存在，且没用别的对象来初始化，就是调用了构造函数；A a; A a = A(1)
对象不存在，且用别的对象来初始化，就是拷贝构造函数   A b = a; A c(a)
对象存在，用别的对象来给它赋值，就是赋值函数 c = b;
 * ***/
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    {
        ConsTruct cons;
        cons.testEmplaceBack();
    }

    return a.exec();
}
