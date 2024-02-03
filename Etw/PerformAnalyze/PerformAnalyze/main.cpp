#include "mainwindow.h"
#include "test/ImagePerform.h"
#include "MyApplication.h"
#include "etw/EtwProvider.h"
int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    MainWindow w;
    w.show();

//    auto imagePer = new ImageTest();
//    imagePer->init();
    return a.exec();
}
