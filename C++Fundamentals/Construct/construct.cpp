#include "construct.h"
#include "test.h"
#include <vector>

static Test s_test = Test(0);
Test getTempTest()
{
    return Test(3);
}

const Test& getLTest()
{
    return s_test;
}

Test&& getRTest()
{
    return Test(2);
}

template <typename T>
void setTest(T&& t)
{
    auto t2 = std::forward(t);
}

void setRTest(Test&& t)
{
    auto t2 = std::move(t);
}

ConsTruct::ConsTruct()
{
}

void ConsTruct::testReturnValue()
{
    {
        qInfo() << "111111 return temp value test begin 111111";
        auto t = getTempTest();
        t.print();
        qInfo() << "******************";
        const auto& lt = getTempTest();
        lt.print();
        qInfo() << "-----------------";
        Test&& rt = getTempTest();
        rt.print();
        qInfo() << "111111 return L value test begin 111111";
        auto t2 = getLTest();
        t2.print();
        qInfo() << "******************";
        const auto& lt2 = getLTest();
        lt2.print();
        qInfo() << "-----------------";
        auto&& rt2 = getLTest();
        rt2.print(); // 注意这里用auto可以，但用Test就不行
        qInfo() << "111111 return R value test begin 111111";
        auto t3 = getRTest();
        t3.print();
        qInfo() << "******************";
        const auto& lt3 = getRTest();
        lt3.print();
        qInfo() << "-----------------";
        Test&& rt3 = getRTest();
        rt3.print();
    }
    {
        qInfo() << "222222 return temp value test begin 22222";
        auto t = getTempTest();
        t.print();
        qInfo() << "******************";
        const auto& lt = getTempTest();
        lt.print();
        qInfo() << "-----------------";
        auto&& rt = getTempTest();
        rt.print();
    }
}

void ConsTruct::testEmplaceBack()
{
    std::vector<Test> testVec;
    testVec.reserve(30);
    // 先构造一个临时对象，再插入到尾端（引入move后就多了一次移动拷贝）
    testVec.push_back(3); // construct right value copy construct
    // 将构造函数的参数完美转发，在容器尾部进行原地构造，无需触发移动拷贝
    testVec.emplace_back(3); // construct 直接传构造函数参数时，两者就有显著的区别了，emplace_back可以减少一次移动拷贝
    // 传入左值或右值的话两者一样，push_back本地调用的是emplace_back
}
