#ifndef LIST_MODEL_H
#define LIST_MODEL_H

#include "listdata.h"
#include <QAbstractTableModel>

class ListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum ListRoles {
        FileIdRole = Qt::UserRole + 1,
        TypeRole,
        NameRole,
        DataEnableRole,
    };
    explicit ListModel(QObject* parent = nullptr);
    ~ListModel() override;

    void insertItem(int row, std::shared_ptr<ListData> item);
    void appendItem(std::shared_ptr<ListData> item);
    void removeItem(int row);
    void removeItem(QModelIndex index);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    // 配合下面两个接口使用
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    // 创建、删除默认行
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;
    bool hasChildren(const QModelIndex& parent) const override;

private:
    QList<std::shared_ptr<ListData>> m_data {};
};

#endif // LIST_MODEL_H
