#include "pluginspec.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QPluginLoader>
#include <QVariant>

class Pluginspec::impl
{
public:
    impl(const QString &path)
        : m_path(path)
    {}

    QString name() const { return m_name; }
    QString version() const { return m_version; }
    QString vendor() const { return m_vendor; }
    QString description() const { return m_description; }
    bool isRequired() const { return m_required; }
    QStringList dependList() const { return m_dependList; }
    void appendDepend(const QString &depend) { m_dependList.append(depend); }
    QJsonObject extension() const { return m_extension; }

    QString path() const { return m_path; }

    bool isLoaded() const { return !m_instance.isNull(); }
    QObject *load()
    {
        QPluginLoader loader(m_path);
        m_instance = loader.instance();
        return m_instance;
    }
    QObject *instance() { return m_instance.data(); }
    void setInstance(QObject *instance) { m_instance = instance; }

    void readMetaData(const QJsonObject &data)
    {
        m_name = data["MetaData"].toObject().value("name").toString();
        m_version = data["MetaData"].toObject().value("version").toString();
        m_vendor = data["MetaData"].toObject().value("vendor").toString();
        m_description = data["MetaData"].toObject().value("description").toString();
        m_required = data["MetaData"].toObject().value("required").toBool();
        auto deps = data["MetaData"].toObject().value("dependencies").toArray().toVariantList();
        for (auto& item : deps) {
            m_dependList.push_back(item.toString());
        }
        if (data["MetaData"].toObject().contains("extension"))
            m_extension = data["MetaData"].toObject().value("extension").toObject();
    }

private:
    QString m_name;
    QString m_version;
    QString m_vendor;
    QString m_description;
    bool m_required;
    QStringList m_dependList;
    QJsonObject m_extension;

    QString m_path;

    QPointer<QObject> m_instance;
};

Pluginspec::Pluginspec(const QString &path)
    : d(new impl(path))
{
}

Pluginspec::~Pluginspec()
{
}

Pluginspec::Pluginspec(const Pluginspec &other)
    : d(new impl(*other.d))
{
}

Pluginspec &Pluginspec::operator=(Pluginspec rhs)
{
    std::swap(d, rhs.d);
    return *this;
}

QString Pluginspec::name() const
{
    return d->name();
}

QString Pluginspec::version() const
{
    return d->version();
}

QString Pluginspec::vendor() const
{
    return d->vendor();
}

QString Pluginspec::description() const
{
    return d->description();
}

bool Pluginspec::isRequired() const
{
    return d->isRequired();
}

QStringList Pluginspec::dependList() const
{
    return d->dependList();
}

void Pluginspec::appendDepend(const QString &depend)
{
    return d->appendDepend(depend);
}

QJsonObject Pluginspec::extension() const
{
    return d->extension();
}

QString Pluginspec::path() const
{
    return d->path();
}

bool Pluginspec::isLoaded() const
{
    return d->isLoaded();
}

QObject *Pluginspec::load()
{
    return d->load();
}

QObject *Pluginspec::instance()
{
    return d->instance();
}

void Pluginspec::setInstance(QObject *instance)
{
    d->setInstance(instance);
}

void Pluginspec::readMetaData(const QJsonObject &data)
{
    d->readMetaData(data);
}

bool Pluginspec::operator==(const Pluginspec &other) const
{
    return d->name() == other.d->name();
}
