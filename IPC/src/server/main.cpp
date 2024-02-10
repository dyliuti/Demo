#include "mainwindow.h"

#include <QApplication>
#include "IPCProtocol/IPCMessageType.h"
#include "ipcservermgr.h"
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTimer::singleShot(5000, [&]{
        QByteArray bytes;
        QDataStream dataStream(&bytes, QIODevice::WriteOnly);
        dataStream << QString("服务发往client测试数据").toLocal8Bit();
        dataStream << false;

        qInfo() << bytes;
        IPCServerMgr::instance().postMessageToClient(PostTest_SC, bytes);
    });

    return a.exec();
}
