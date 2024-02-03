#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QObject>
#include <QElapsedTimer>

class ImageTest : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;
    void readImage();
    void secondLoad(QStringList strList);
private:
    QElapsedTimer m_funcTimer;
};

#endif // MYAPPLICATION_H
