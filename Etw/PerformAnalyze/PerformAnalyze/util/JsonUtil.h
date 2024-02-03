#ifndef JSONUTIL_H
#define JSONUTIL_H
#include <QString>
#include <QJsonObject>

class JsonUtil
{
public:
    static QJsonObject convertStringToJsonObj(const QString& json);
    static QString convertJsonObjToString(const QJsonObject& obj);
};

#endif // EEOJSONUTIL_H
