#ifndef PLUGINSPEC_H
#define PLUGINSPEC_H

#include "define.h"

#include <QString>
#include <QObject>
#include <memory>

class EXTENSION_EXPORT Pluginspec : public QObject
{
    Q_OBJECT
public:
    Pluginspec(const QString &path);
    ~Pluginspec();

    Pluginspec(const Pluginspec &other);
    Pluginspec &operator=(Pluginspec rhs);

    QString name() const;
    QString version() const;
    QString vendor() const;
    QString description() const;
    bool isRequired() const;
    QStringList dependList() const;
    void appendDepend(const QString &depend);
    QJsonObject extension() const;
    QString path() const;

    bool isLoaded() const;
    QObject *load();
    QObject *instance();
    void setInstance(QObject *instance);

    void readMetaData(const QJsonObject &data);

    bool operator==(const Pluginspec &other) const;

private:
    class impl;
    std::unique_ptr<impl> d;
};

#endif
