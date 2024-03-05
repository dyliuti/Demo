#include "listview.h"
#include "listdelegate.h"
#include <QDebug>

ListView::ListView(QWidget* parent)
    : QListView(parent)
{
    setItemAlignment(Qt::AlignLeft);
    setStyleSheet("QListView { border: none; margin: 0px; padding: 0px 1px; background-color: transparent;}");
    setSpacing(0);
}

ListView::~ListView()
{
    qInfo() << "333333: " << __FUNCTION__;
}
