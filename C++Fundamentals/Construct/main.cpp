#include <QCoreApplication>
#include <QDebug>
#include "test.h"

static Test s_test = Test(0);
Test getTempTest() {
    return Test(3);
}

const Test& getLTest() {
    return s_test;
}

Test&& getRTest() {
    return Test(2);
}

template <typename T>
void setTest(T&& t) {
    auto t2 = std::forward(t);
}

void setRTest(Test&& t) {
    auto t2 = std::move(t);
}
/***
对象不存在，且没用别的对象来初始化，就是调用了构造函数；A a; A a = A(1)
对象不存在，且用别的对象来初始化，就是拷贝构造函数   A b = a; A c(a)
对象存在，用别的对象来给它赋值，就是赋值函数 c = b;
 * ***/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    {
        qInfo() << "111111 return temp value test begin 111111";
        auto t = getTempTest(); t.print();
        qInfo() << "******************";
        const auto& lt = getTempTest(); lt.print();
        qInfo() << "-----------------";
        Test&& rt = getTempTest(); rt.print();
        qInfo() << "111111 return L value test begin 111111";
        auto t2 = getLTest(); t2.print();
        qInfo() << "******************";
        const auto& lt2 = getLTest(); lt2.print();
        qInfo() << "-----------------";
        auto&& rt2 = getLTest(); rt2.print();    // 注意这里用auto可以，但用Test就不行
        qInfo() << "111111 return R value test begin 111111";
        auto t3 = getRTest(); t3.print();
        qInfo() << "******************";
        const auto& lt3 = getRTest(); lt3.print();
        qInfo() << "-----------------";
        Test&& rt3 = getRTest(); rt3.print();
    }
    {
        qInfo() << "222222 return temp value test begin 22222";
        auto t = getTempTest(); t.print();
        qInfo() << "******************";
        const auto& lt = getTempTest(); lt.print();
        qInfo() << "-----------------";
        auto&& rt = getTempTest(); rt.print();
    }
    return a.exec();
}
