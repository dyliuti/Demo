#include "mainwindow.h"

#include <QApplication>
#include "startupobject.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartupObject startupObject;
    QTimer::singleShot(0, &startupObject, &StartupObject::delayedInit);

    MainWindow w;
    w.show();
    return a.exec();
}
