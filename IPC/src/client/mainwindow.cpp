#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_label = new QLabel(this);
    m_label->setText("nihao Im client");
    layout()->addWidget((QWidget*)m_label);
}

void MainWindow::setText(QString text)
{
    m_label->setText(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

