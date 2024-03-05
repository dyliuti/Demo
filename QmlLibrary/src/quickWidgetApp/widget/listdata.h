#ifndef LIST_DATA_H
#define LIST_DATA_H

#include <QObject>

class ListData : public QObject {
    Q_OBJECT

public:
    enum Type {
        PPT,
        EXCEL,
        WORD,
        PDF,
        SpliteLine,
        EXPANSION_BOARD,
        MAIN_BOARD
    };
    Q_ENUM(Type)

public:
    explicit ListData(QObject* parent = nullptr);
    explicit ListData(QString showName, quint64 fileId, ListData::Type type, QObject* parent = nullptr);
    ~ListData();

    Q_PROPERTY(quint64 fileId READ fileId WRITE setFileId NOTIFY sigFileIdChanged);
    Q_PROPERTY(QString showName READ showName WRITE setShowName NOTIFY sigShowNameChanged);
    Q_PROPERTY(ListData::Type type READ type WRITE setType);
    Q_PROPERTY(bool dataEnable READ dataEnable WRITE setDataEnable NOTIFY sigDataEnableChanged);

    quint64 fileId() const;
    void setFileId(quint64 newFileId);
    const QString& showName() const;
    void setShowName(const QString& newShowName);
    ListData::Type type() const;
    void setType(ListData::Type newType);

    bool dataEnable() const;
    void setDataEnable(bool newDataEnable);

signals:
    void sigFileIdChanged();
    void sigShowNameChanged();

    void sigDataEnableChanged();

private:
    QString m_showName;
    quint64 m_fileId;
    ListData::Type m_type;
    bool m_dataEnable = false;
};

#endif // LIST_DATA_H
