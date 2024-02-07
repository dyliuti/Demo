#include <QApplication>
#include <qquickwidget.h>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQuickWidget *view = new QQuickWidget;
    qInfo() << "123456: " << QCoreApplication::applicationDirPath();
//    view->engine()->addImportPath(QCoreApplication::applicationDirPath());
    view->setSource(QUrl("qrc:/demo/demoqml/Test.qml"));
    view->show();

    return a.exec();
}
