#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test/ImagePerform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QObject obj;
//    connect(&obj, &QObject::destroyed, this, [&](){
//        auto imagePer = new ImageTest();
//        imagePer->init();
//    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    auto imagePer = new ImageTest();
    imagePer->readImage();
    QMainWindow::mousePressEvent(event);
}

