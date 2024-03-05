#ifndef LIST_DELEGATE_H
#define LIST_DELEGATE_H

#include <QStyledItemDelegate>

class ListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

public:
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

class SpliteLineDelegate : public ListDelegate {
    Q_OBJECT
public:
    using ListDelegate::ListDelegate;

public:
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // LIST_DELEGATE_H
