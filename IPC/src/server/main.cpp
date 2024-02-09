#include "mainwindow.h"

#include <QApplication>
#include "IPCProtocol/IPCMessageHelper.h"
#include "ipcservermgr.h"
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTimer::singleShot(15000, [&]{
        IPCServerMgr::instance().postMessageToClient(PostTest_SC, "服务发往client测试数据");
    });

    return a.exec();
}
