#ifndef BACKGROUNDDECORATION_H
#define BACKGROUNDDECORATION_H

#include <QMargins>
#include <QObject>

class QWidget;

class BackgroundDecoration : public QObject {
    Q_OBJECT
public:
    explicit BackgroundDecoration(QWidget* decoratedWidget, const QString& backgroundImage, const QMargins& margins = QMargins(6, 6, 6, 6));
    ~BackgroundDecoration();

    static QString RoundRectImage;
    static QString LightRoundRectImage;
    static QString NewRoundRectImage;

    void setBackgorundImage(const QString& image);

private:
    bool eventFilter(QObject* o, QEvent* e) override;

    QString m_backgroundImage;
    QMargins m_margins;
};

class BackgroundDownArrowDecoration : public QObject {
    Q_OBJECT
public:
    explicit BackgroundDownArrowDecoration(QWidget* decoratedWidget);

private:
    bool eventFilter(QObject* o, QEvent* e) override;

    QMargins m_margins;
};

class BackgroundArrowDecoration : public QObject {
    Q_OBJECT
public:
    explicit BackgroundArrowDecoration(QWidget* decoratedWidget, Qt::ArrowType type, bool isBlue = true);

private:
    bool eventFilter(QObject* o, QEvent* e) override;

    QMargins m_margins;
    Qt::ArrowType m_type;
    QString imagePath;
};

class TipBackgroundArrowDecoration : public QObject {
    Q_OBJECT
public:
    explicit TipBackgroundArrowDecoration(QWidget* decoratedWidget, Qt::ArrowType type, int padding = -1);

private:
    bool eventFilter(QObject* o, QEvent* e) override;

    QMargins m_margins;
    Qt::ArrowType m_type;
    QString imagePath;
    int m_padding = -1;
};

#endif // BACKGROUNDDECORATION_H
