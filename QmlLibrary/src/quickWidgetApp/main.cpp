#include "widget/BackgroundDecoration.h"
#include "widget/listdelegate.h"
#include "widget/listmodel.h"
#include "widget/listview.h"
#include <QApplication>
#include <QItemSelectionModel>
#include <QQmlEngine>
#include <QVBoxLayout>
#include <QWidget>
#include <qquickwidget.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //    QQuickWidget* view = new QQuickWidget;
    //    qInfo() << "123456: " << QCoreApplication::applicationDirPath();
    //    //    view->engine()->addImportPath(QCoreApplication::applicationDirPath());
    //    view->setSource(QUrl("qrc:/demo/demoqml/Test.qml"));
    //    view->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //    view->setFixedSize(800, 600);
    //    view->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //    new BackgroundDecoration(view, BackgroundDecoration::RoundRectImage);
    //    view->show();

    QWidget* w = new QWidget;
    w->setAttribute(Qt::WA_TranslucentBackground, true);
    w->setFixedSize(220, 266);
    w->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    auto layout = new QVBoxLayout(w);
    layout->setContentsMargins(0, 8, 0, 8);
    ListView* listview = new ListView();
    listview->setFixedHeight(266 - 8 * 2);
    layout->addWidget(listview);
    w->setLayout(layout);

    // 设置model
    auto model = new ListModel(listview);
    listview->setModel(model);
    model->appendItem(std::make_shared<ListData>("扩展黑板", 0, ListData::EXPANSION_BOARD));
    model->appendItem(std::make_shared<ListData>("pdf", 1, ListData::PDF));
    model->appendItem(std::make_shared<ListData>("word", 2, ListData::WORD));
    model->appendItem(std::make_shared<ListData>("excel", 3, ListData::EXCEL));
    model->appendItem(std::make_shared<ListData>("ppt", 4, ListData::PPT));
    model->appendItem(std::make_shared<ListData>("spliteline", -1, ListData::SpliteLine));
    model->appendItem(std::make_shared<ListData>("主教室", 5, ListData::MAIN_BOARD));

    //    model->insertItem(2, std::make_shared<ListData>("主教室", 6, ListData::MAIN_BOARD));
    // 设置delete item
    auto listDelegate = new ListDelegate((QObject*)listview);
    auto spliteLineDelegate = new SpliteLineDelegate((QObject*)listview);

    listview->setItemDelegate(listDelegate);
    if (model->rowCount() >= 2) {
        listview->setItemDelegateForRow(model->rowCount() - 2, spliteLineDelegate);
    }

    // 设置选中项
    //    listview->setSelectionMode(QListView::SingleSelection);
    auto selectionModel = listview->selectionModel();
    selectionModel->select(model->index(1, 0), QItemSelectionModel::Select);

    // 设置dataEnbale
    model->setData(model->index(2, 0), true, ListModel::DataEnableRole);
    new BackgroundDecoration(w, BackgroundDecoration::RoundRectImage);
    w->show();
    //    w->deleteLater();

    return a.exec();
}
