#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PerformAnalyze.h"

class PerformAnalyze : public QMainWindow
{
    Q_OBJECT

public:
    PerformAnalyze(QWidget *parent = nullptr);
    ~PerformAnalyze();

private:
    Ui::PerformAnalyzeClass ui;
};
