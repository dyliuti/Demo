#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "ipcclientmgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qInfo() << "222222: " << argc;

    if(argc >= 2) {
        qInfo() << "222222: " << argv[0] << argv[1];
        IPCClientMgr::instance().init(QString::fromStdString(argv[1]).toInt());
        w.setText("我是client, 服务端口: " + QString::fromStdString(argv[1]));

        QObject::connect(&IPCClientMgr::instance(), &IPCClientMgr::sigClientMsg, [&](QString msg){
            w.setText(msg);
        });
    } else {
        IPCClientMgr::instance().init(7733);
        w.setText("我是client, 服务端口: 7733");

      QObject::connect(&IPCClientMgr::instance(), &IPCClientMgr::sigClientMsg, &w, [&](QString msg){
          w.setText(msg);
      });
    }
    return a.exec();
}
