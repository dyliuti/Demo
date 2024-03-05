#include "listmodel.h"
#include <QDebug>

ListModel::ListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

ListModel::~ListModel()
{
    qInfo() << "333333: " << __FUNCTION__;
    m_data.clear();
}

void ListModel::insertItem(int row, std::shared_ptr<ListData> item)
{
    // 前插
    beginInsertRows(QModelIndex(), row, row);
    m_data.insert(row, item);
    endInsertRows();
}

void ListModel::appendItem(std::shared_ptr<ListData> item)
{
    const int index = m_data.size();
    beginInsertRows(QModelIndex(), index, index);
    m_data.append(item);
    endInsertRows();

    //    insertRows(m_data.size(), 1);
    //    setData(index(m_data.size() - 1, 0), item->showName(), ListModel::NameRole);
    //    setData(index(m_data.size() - 1, 0), item->type(), ListModel::TypeRole);
    //    setData(index(m_data.size() - 1, 0), item->fileId(), ListModel::FileIdRole);
}

void ListModel::removeItem(int row)
{
    //    beginRemoveRows(QModelIndex(),index.row(),index.row());
    //    m_data.removeAt(index.row());
    //    endRemoveRows();

    removeRows(row, 1);
}

void ListModel::removeItem(QModelIndex index)
{
    removeRows(index.row(), 1);
}

bool ListModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        m_data.insert(row, std::make_shared<ListData>());
    }
    endInsertRows();
    return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex& parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        m_data.removeAt(row);
    }
    endRemoveRows();
    return true;
}

int ListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

QVariant ListModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    auto data = m_data[index.row()];
    switch (role) {
    case NameRole: {
        return data->showName();
    }
    case TypeRole: {
        return data->type();
    }
    case FileIdRole: {
        return data->fileId();
    }
    default: {
        break;
    }
    }

    return QVariant();
}

bool ListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    auto data = m_data[index.row()];
    switch (role) {
    case NameRole: {
        if (data->showName() != value.toString()) {
            data->setShowName(value.toString());
            emit dataChanged(index, index);
        }
        break;
    }

    case TypeRole: {
        if (data->showName() != value.toString()) {
            data->setShowName(value.toString());
            emit dataChanged(index, index);
        }
        break;
    }

    case FileIdRole: {
        if (data->showName() != value.toString()) {
            data->setShowName(value.toString());
            emit dataChanged(index, index);
        }
        break;
    }
    default: {
        return false;
    }
    }

    return true;
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileIdRole] = "fileId";
    roles[TypeRole] = "type";
    roles[NameRole] = "showName";

    return roles;
}

bool ListModel::hasChildren(const QModelIndex& parent) const
{
    return rowCount(parent) > 0;
}
