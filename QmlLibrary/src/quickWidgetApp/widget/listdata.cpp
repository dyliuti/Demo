#include "listdata.h"
#include <QDebug>

ListData::ListData(QObject* parent)
    : QObject(parent)
{
}

ListData::ListData(QString showName, quint64 fileId, ListData::Type type, QObject* parent)
    : QObject(parent)
    , m_showName(showName)
    , m_fileId(fileId)
    , m_type(type)
{
}

ListData::~ListData()
{
    qInfo() << "333333: " << __FUNCTION__;
}

quint64 ListData::fileId() const
{
    return m_fileId;
}

void ListData::setFileId(quint64 newFileId)
{
    if (m_fileId == newFileId)
        return;
    m_fileId = newFileId;
    emit sigFileIdChanged();
}

const QString& ListData::showName() const
{
    return m_showName;
}

void ListData::setShowName(const QString& newShowName)
{
    if (m_showName == newShowName)
        return;
    m_showName = newShowName;
    emit sigShowNameChanged();
}

ListData::Type ListData::type() const
{
    return m_type;
}

void ListData::setType(ListData::Type newType)
{
    m_type = newType;
}

bool ListData::dataEnable() const
{
    return m_dataEnable;
}

void ListData::setDataEnable(bool newDataEnable)
{
    if (m_dataEnable == newDataEnable)
        return;
    m_dataEnable = newDataEnable;
    emit sigDataEnableChanged();
}
