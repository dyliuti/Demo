#ifndef DATETIMEITEM_H
#define DATETIMEITEM_H

#include <QQuickItem>
#include <QQuickPaintedItem>

class DateTimeItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(DateTimeItem)

public:
    explicit DateTimeItem(QQuickItem *parent = nullptr);
    ~DateTimeItem() override;

    void paint(QPainter *painter) override;

private:
    QString getClockText();

private:
    QTimer *m_timer = nullptr;
    QFont m_font;
};

#endif // DATETIMEITEM_H
