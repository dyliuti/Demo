#include "construct.h"
#include "test.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

struct President {
    std::string name;
    std::string country;
    int year;

    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name))
        , country(std::move(p_country))
        , year(p_year)
    {
        qInfo() << "I am being constructed.\n";
    }
    President(const President& other)
        : name(std::move(other.name))
        , country(std::move(other.country))
        , year(other.year)
    {
        qInfo() << "I am being copy constructed.\n";
    }
    President(President&& other)
        : name(std::move(other.name))
        , country(std::move(other.country))
        , year(other.year)
    {
        qInfo() << "I am being moved.\n";
    }
    President& operator=(const President& other);
};

/***
对象不存在，且没用别的对象来初始化，就是调用了构造函数；A a; A a = A(1)
对象不存在，且用别的对象来初始化，就是拷贝构造函数   A b = a; A c(a)
对象存在，用别的对象来给它赋值，就是赋值函数 c = b;
 * ***/
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    {
        //                ConsTruct cons;
        //                cons.testEmplaceBack();

        std::vector<President> elections;
        qInfo() << "emplace_back:\n";
        elections.emplace_back("Nelson Mandela", "South Africa", 1994); // 没有类的创建

        std::vector<President> reElections;
        qInfo() << "\npush_back:\n";
        reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

        qInfo() << "\nContents:\n";
        for (President const& president : elections) {
            qInfo() << QString::fromStdString(president.name) << " was elected president of " << QString::fromStdString(president.country) << " in " << president.year << ".\n";
        }
        for (President const& president : reElections) {
            qInfo() << QString::fromStdString(president.name) << " was re-elected president of " << QString::fromStdString(president.country) << " in " << president.year << ".\n";
        }
    }

    return a.exec();
}
