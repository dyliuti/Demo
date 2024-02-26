#include "DateTimeItem.h"
#include <QDateTime>
#include <QPainter>
#include <QTimer>
#include <QFontDatabase>
#include <QDate>
#include <QTime>
//#include "LauncherxUtil.h"

DateTimeItem::DateTimeItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    //    int fontId = QFontDatabase::addApplicationFont("qrc:/font/font/gry.otf");
    //    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    //    m_font = QFont(fontName, 12);

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, [&]() {
        update();
    });

    m_timer->start();
}

DateTimeItem::~DateTimeItem()
{
}

void DateTimeItem::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);

    //    painter->setFont(m_font);
    painter->setPen(Qt::white);
    auto txt = getClockText(); // + "\n" + LauncherxUtil::getLauncherxDateTime();
    //    painter->drawText(QPoint(0, 0), Qt::AlignRight, getClockText());
    painter->drawText(boundingRect(), Qt::AlignRight, txt);
}

QString DateTimeItem::getClockText()
{
    QTime time = QTime::currentTime();
    auto hours = time.hour();
    auto minutes = time.minute();
    if (minutes < 10) {
        return QString("%1:0%2").arg(hours).arg(minutes);
    }

    return QString("%1:%2").arg(hours).arg(minutes);
}
