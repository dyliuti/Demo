#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "extension/extension.h"
#include "plugin1/plugin1Mgr.h"
#include "plugin2/plugin2Mgr.h"
#include "plugin1/plugin1Test.h"
#include "plugin2/plugin2Test.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    auto plugin1Mgr = Extension::instance()->getObject<Plugin1Mgr>();
//    if(plugin1Mgr) {
//        const auto& plugin1Test = plugin1Mgr->getPlugin1Test();
//        if(plugin1Test) {
//            qInfo() << "777777 plugin1 multir: " << __FUNCTION__ << plugin1Test->multi(3, 5);
//        }
//    }

//    auto plugin2Mgr = Extension::instance()->getObject<Plugin2Mgr>();
//    if(plugin2Mgr) {
//        const auto& plugin2Test = plugin2Mgr->getPlugin2Test();
//        if(plugin2Test) {
//            qInfo() << "777777 plugin2 add: " << __FUNCTION__ << plugin2Test->add(3, 5);
//        }
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

