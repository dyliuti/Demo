#include "pluginfactoryloader.h"
#include "extension.h"
#include "pluginmanager.h"

#include <queue>
#include <QByteArray>
#include <QString>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>

class PluginFactoryLoader::impl
{
public:
    impl(PluginFactoryLoader *pd, const char *iid, const QString &suffix, Qt::CaseSensitivity cs)
        : p(pd)
        , m_iid(iid)
        , m_suffix(suffix)
        , m_cs(cs)
    {
    }
    ~impl() { qDeleteAll(m_pluginList); }

    void load()
    {
        QDir pluginsDir(PluginManager::instance()->path() + QDir::separator() + m_suffix);
        pluginsDir.setFilter(QDir::Files | QDir::NoSymLinks);

        int index = 0;
        QMap<QString, int> idIndexMap;
        QMap<QString, Pluginspec *> idPlguinMap;
        for (const QFileInfo &info : pluginsDir.entryInfoList()) {
            QPluginLoader loader(info.filePath());
            auto metaData = loader.metaData();
            if (metaData.value("IID").toString() != m_iid) {
                qWarning() << "mismatching iid : " << info.filePath();
                continue;
            }
            Pluginspec *spec = new Pluginspec(info.filePath());
            spec->readMetaData(metaData);
            idIndexMap.insert(spec->name(), index++);
            idPlguinMap.insert(spec->name(), spec);
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
            p->preload(item);
        }
    }

    QObject *load(Pluginspec *spec)
    {
        if (spec->isLoaded()) {
            return spec->instance();
        }
        loadDepends(spec);
        return spec->load();
    }

    QList<Pluginspec *> pluginList() { return m_pluginList; }

protected:
    void loadDepends(Pluginspec *spec)
    {
        auto deps = spec->dependList();
        for (auto &dep : deps) {
            auto iter = std::find_if(
                m_pluginList.begin(), m_pluginList.end(), [=](Pluginspec *item) {
                    return item->name() == dep;
                });
            if (iter != m_pluginList.end() && !(*iter)->isLoaded()) {
                loadDepends(*iter);
                (*iter)->load();
            }
        }
    }

private:
    PluginFactoryLoader *p = nullptr;

    QByteArray m_iid;
    const QString m_suffix;
    Qt::CaseSensitivity m_cs;
    QList<Pluginspec *> m_pluginList;
};

PluginFactoryLoader::PluginFactoryLoader(const char *iid,
                                         const QString &suffix,
                                         Qt::CaseSensitivity cs)
    : d(new impl(this, iid, suffix, cs))
{
}

PluginFactoryLoader::~PluginFactoryLoader() = default;

void PluginFactoryLoader::load()
{
    d->load();
}

QList<Pluginspec *> PluginFactoryLoader::pluginList()
{
    return d->pluginList();
}

QObject *PluginFactoryLoader::load(Pluginspec *spec)
{
    return d->load(spec);
}
