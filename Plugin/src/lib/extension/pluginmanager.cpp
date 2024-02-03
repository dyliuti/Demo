#include "pluginmanager.h"
#include "iplugin.h"

#include <queue>
#include <vector>
#include <sstream>
#include <QDir>
#include <QPluginLoader>
#include <QMultiMap>
#include <QDebug>
#include <QMessageBox>

class PluginManager::impl
{
public:
    ~impl() { qDeleteAll(m_pluginList); }

    QList<Pluginspec *> pluginList()
    {
        return m_pluginList;
    }

    void loadPlugins(const char *iid, const QString &dir)
    {
        if (m_bLoaded) {
            return;
        }
        m_path = dir;
        m_bLoaded = true;

        static std::vector<std::string> checkPlugins{"plugin1", "plugin2"};
        auto tmpCheckPlugins = checkPlugins;

        QDir pluginsDir = dir;
        pluginsDir.setFilter(QDir::Files | QDir::NoSymLinks);

        int index = 0;
        QMap<QString, int> idIndexMap;
        QMap<QString, Pluginspec *> idPlguinMap;
        QStringList nameFilters;
#if defined Q_OS_WINDOWS
        nameFilters << "*.dll";
#elif defined Q_OS_MACOS
        nameFilters << "*.dylib";
#elif defined Q_OS_LINUX
        nameFilters << "*.so";
#endif
        const auto& entryInfoList = pluginsDir.entryInfoList(nameFilters);
        for (const QFileInfo &info : entryInfoList) {
            QString pluginName = info.baseName();
            if (pluginName.startsWith("lib")) {
                pluginName.remove(0, 3);
            }
            auto iter = std::find(tmpCheckPlugins.begin(), tmpCheckPlugins.end(), pluginName.toStdString());
            bool bFind = iter != tmpCheckPlugins.end();
            if (bFind) {
                tmpCheckPlugins.erase(iter);
            }

            QPluginLoader loader(info.filePath());
            if (!loader.load()) {
                qInfo() << "load failed: " << info.filePath() << loader.errorString();
                if (bFind)
                    QMessageBox::warning(nullptr, "ClassIn", QString("plugin load failed: %1").arg(loader.errorString()));
                continue;
            }
            auto metaData = loader.metaData();
            if (metaData.value("IID").toString() != iid) {
                qInfo() << "mismatching iid : " << info.filePath();
                continue;
            }

            Pluginspec *spec = new Pluginspec(info.filePath());
            spec->readMetaData(metaData);
            spec->setInstance(loader.instance());
            idIndexMap.insert(spec->name(), index++);
            idPlguinMap.insert(spec->name(), spec);
        }

        if (!tmpCheckPlugins.empty()) {
            std::ostringstream oss;
            std::copy(tmpCheckPlugins.begin(), tmpCheckPlugins.end() - 1, std::ostream_iterator<std::string>(oss, ","));
            oss << tmpCheckPlugins.back();
            std::string joinedStr = oss.str();
            QMessageBox::warning(nullptr, "ClassIn", QString("missing plugins: %1").arg(QString::fromStdString(joinedStr)));
        }

        if (idIndexMap.isEmpty()) {
            qWarning() << "no plugins";
            return;
        }

        std::vector<std::vector<int>> dependencies;
        for (Pluginspec *p : idPlguinMap.values()) {
            for (const QString &depId : p->dependList()) {
                dependencies.push_back({idIndexMap.value(p->name()), idIndexMap.value(depId)});
            }
        }

        auto topologicalSort = [](std::vector<std::vector<int>> &dependencies, int numCourses) -> std::vector<int> {
            std::vector<int> indegree(numCourses, 0);
            std::vector<std::vector<int>> adjList(numCourses);

            for (auto &dependency : dependencies) {
                int prerequisite = dependency[1];
                int course = dependency[0];
                adjList[prerequisite].push_back(course);
                indegree[course]++;
            }

            std::vector<int> sortedOrder;
            std::queue<int> q;

            for (int i = 0; i < numCourses; i++) {
                if (indegree[i] == 0) {
                    q.push(i);
                }
            }

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                sortedOrder.push_back(node);

                for (int neighbor : adjList[node]) {
                    indegree[neighbor]--;
                    if (indegree[neighbor] == 0) {
                        q.push(neighbor);
                    }
                }
            }

            if (sortedOrder.size() != numCourses) {
                return std::vector<int>();
            }

            return sortedOrder;
        };

        std::vector<int> result = topologicalSort(dependencies, index);
        if (result.empty()) {
            qWarning() << "the topology sort cannot be completed because a ring exists procedure";
            return;
        }

        QMultiMap<int, Pluginspec *> deps;
        QMapIterator<QString, int> i(idIndexMap);
        while (i.hasNext()) {
            i.next();
            deps.insert(i.value(), idPlguinMap.value(i.key()));
        }
        for (int index : result) {
            m_pluginList.append(deps.values(index));
        }

        for (auto &item : m_pluginList) {
            qInfo() << "bengin load plugin" << item->name();
            IPlugin *instance = qobject_cast<IPlugin *>(item->instance());
            if (instance)
                instance->load();
            qInfo() << "end load plugin" << item->name();
        }
    }

    bool isLoaded() const { return m_bLoaded; }

    QString path() const { return m_path; }

private:
    QString m_path;
    bool m_bLoaded = false;
    QList<Pluginspec *> m_pluginList;
};

PluginManager *PluginManager::instance()
{
    static PluginManager manager;
    return &manager;
}

PluginManager::PluginManager(QObject *parent)
    : QObject(parent)
    , d(new impl)
{
}

PluginManager::~PluginManager()
{
}

QList<Pluginspec *> PluginManager::pluginList()
{
    return d->pluginList();
}

void PluginManager::loadPlugins(const char *iid, const QString &dir)
{
    d->loadPlugins(iid, dir);

    emit loaded();
}

bool PluginManager::isLoaded() const
{
    return d->isLoaded();
}

QString PluginManager::path() const
{
    return d->path();
}
