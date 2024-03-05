#ifndef EXPANSION_LIST_WIDGET_H
#define EXPANSION_LIST_WIDGET_H

#include "listmodel.h"
#include <QListView>
#include <QWidget>

class ListView;
class ListModel;
class ListData;
class ListDelegate;
class SpliteLineDelegate;
class ExpansionListWidget : public QWidget {
    Q_OBJECT

public:
    explicit ExpansionListWidget(QWidget* parent = nullptr);
    ListModel* getModel() { return m_model; }

private:
    ListView* m_listview = nullptr;
    ListModel* m_model = nullptr;
    ListDelegate* m_listDelegate = nullptr;
    SpliteLineDelegate* m_spliteLienDelegate = nullptr;
};

#endif // EXPANSION_LIST_WIDGET_H
