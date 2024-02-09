#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayout>
#include <QLabel>
#include <QCoreApplication>
#include <ipcservermgr.h>
#include "IPCProtocol/IPCMessageHelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    lay
    auto label = new QLabel(this);
    label->setText("nihao Im server");
    layout()->addWidget((QWidget*)label);

    // 启动server
    IPCServerMgr::instance();

    // 开启client
//    QStringList param;
//    param << QString::number(7733) << "我是server";
////    param << QString::number(IPCServerMgr::instance().serverPort()) << "我是server";
//    qInfo() << "111111 server: " << QCoreApplication::applicationDirPath() + "/client.exe";
//    m_process.start(QCoreApplication::applicationDirPath() + "/client.exe", param);
//    m_process.waitForStarted();

//    IPCServerMgr::instance().returnMessageToClient("回复数据");

//    qInfo() << "111111 server: " << param;
}

MainWindow::~MainWindow()
{
    delete ui;
}

