#include <QApplication>
#include <QQmlEngine>
#include <qquickwidget.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QQuickWidget* view = new QQuickWidget;
    qInfo() << "123456: " << QCoreApplication::applicationDirPath();
    //    view->engine()->addImportPath(QCoreApplication::applicationDirPath());
    view->setSource(QUrl("qrc:/demo/demoqml/Test.qml"));
    view->setResizeMode(QQuickWidget::SizeRootObjectToView);
    view->setFixedSize(800, 600);
    view->show();

    return a.exec();
}
