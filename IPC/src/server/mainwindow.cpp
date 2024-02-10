#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayout>
#include <QLabel>
#include <QCoreApplication>
#include <ipcservermgr.h>
#include "IPCProtocol/IPCMessageType.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    lay
    m_label = new QLabel(this);
    m_label->setText("你好，我是服务");
    layout()->addWidget((QWidget*)m_label);

    // 启动server
    IPCServerMgr::instance();
    connect(&IPCServerMgr::instance(), &IPCServerMgr::sigNewMessage, this, [&](QString data){
        m_label->setText(data);
    });
    // 开启client
//    QStringList param;
////    param << QString::number(7733) << "我是server";
//    param << QString::number(IPCServerMgr::instance().serverPort()) << "我是server";
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

void MainWindow::setText(QString text)
{
    m_label->setText(text);
}
