#ifndef LIST_VIEW_H
#define LIST_VIEW_H

#include "listmodel.h"
#include <QListView>
#include <QWidget>

class ListView : public QListView {
    Q_OBJECT

public:
    explicit ListView(QWidget* parent = nullptr);
    ~ListView();

private:
    ListModel* model = nullptr;
};

#endif // LIST_VIEW_H
