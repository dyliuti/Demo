#include "expansionlistwidget.h"
#include "BackgroundDecoration.h"
#include "listdelegate.h"
#include "listmodel.h"
#include "listview.h"
#include <QDebug>
#include <QVBoxLayout>

ExpansionListWidget::ExpansionListWidget(QWidget* parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(220, 266);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 8, 0, 8);
    m_listview = new ListView();
    m_listview->setFixedHeight(266 - 8 * 2);
    layout->addWidget(m_listview);
    setLayout(layout);

    // 设置model
    auto model = new ListModel(m_listview);
    m_listview->setModel(model);
    //    model->appendItem(std::make_shared<ListData>("扩展黑板", 0, ListData::EXPANSION_BOARD));
    //    model->appendItem(std::make_shared<ListData>("pdf", 1, ListData::PDF));
    //    model->appendItem(std::make_shared<ListData>("word", 2, ListData::WORD));
    //    model->appendItem(std::make_shared<ListData>("excel", 3, ListData::EXCEL));
    //    model->appendItem(std::make_shared<ListData>("ppt", 4, ListData::PPT));
    model->appendItem(std::make_shared<ListData>("spliteline", -1, ListData::SpliteLine));
    model->appendItem(std::make_shared<ListData>("主教室", 5, ListData::MAIN_BOARD));

    // 设置delete item
    auto listDelegate = new ListDelegate((QObject*)m_listview);
    auto spliteLineDelegate = new SpliteLineDelegate((QObject*)m_listview);

    m_listview->setItemDelegate(listDelegate);
    if (model->rowCount() >= 2) {
        m_listview->setItemDelegateForRow(model->rowCount() - 2, spliteLineDelegate);
    }

    // 设置选中项
    //    listview->setSelectionMode(QListView::SingleSelection);
    auto selectionModel = m_listview->selectionModel();
    selectionModel->select(model->index(1, 0), QItemSelectionModel::Select);

    // 设置dataEnbale
    model->setData(model->index(2, 0), true, ListModel::DataEnableRole);
    new BackgroundDecoration(this, BackgroundDecoration::RoundRectImage);
}
