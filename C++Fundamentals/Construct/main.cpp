#include <QCoreApplication>
#include <QDebug>

class Test {
public:
    Test(int a) : m_a(a) {qInfo() << "construct";};
    Test(const Test& a){
        qInfo() << "left value copy construct";
    }
    Test(Test&& a){
        qInfo() << "right value copy construct";
    }

    void operator=(const Test& a) {
        qInfo() << "left value copy assignment construct";
    }

    void operator=(Test&& a) {
        qInfo() << "right value move assignment construct";
    }
    void print() const {qInfo() << m_a;}
private:
    int m_a = 0;
};

const Test& createTest() {
//    auto t = ;
    return Test(1);
}

void copyTest(const Test& t) {
    auto t2 = t;
}

void copyTest(Test&& t) {
    auto t2 = t;
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
        auto t = createTest();
        t.print();
    }
//    auto t = Test(2);
//    copyTest(t);
//    copyTest(Test(2));
//    Test t  = Test(3);
//    Test t2 = 4;
//    t2 = std::move(t);
    return a.exec();
}
