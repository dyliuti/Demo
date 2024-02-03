#ifndef MY_APPLICATION_H
#define MY_APPLICATION_H

#include <QApplication>
#include <QObject>
#include <QElapsedTimer>

class MyApplication : public QApplication {
    Q_OBJECT
public:
    MyApplication(int &argc, char **argv);
    bool notify(QObject *, QEvent *) override;

protected:
    bool isEventNeed(QEvent *e);

private:
    QElapsedTimer m_funcTimer;
};

#endif // MY_APPLICATION_H
