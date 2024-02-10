﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "ipcservermgr.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setText(QString text);

private:
    Ui::MainWindow *ui;

    QProcess m_process;
//    IPCServerMgr* m_ipcServerMgr = nullptr;
    QLabel* m_label = nullptr;
};
#endif // MAINWINDOW_H
