#include "BackgroundDecoration.h"
#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QSvgRenderer>
#include <QWidget>
#include <qdrawutil.h>

QString BackgroundDecoration::RoundRectImage(":/com/img/roundrect_background.svg");
QString BackgroundDecoration::LightRoundRectImage(":/com/img/light_roundrect_background.svg");
QString BackgroundDecoration::NewRoundRectImage("newRoundRectImage");

BackgroundDecoration::BackgroundDecoration(QWidget* decoratedWidget, const QString& backgroundImage, const QMargins& margins)
    : QObject(decoratedWidget)
    , m_backgroundImage(backgroundImage)
    , m_margins(margins)
{
    if (decoratedWidget) {
        decoratedWidget->installEventFilter(this);
    }
}

BackgroundDecoration::~BackgroundDecoration()
{
    qInfo() << "333333: " << __FUNCTION__;
}

bool BackgroundDecoration::eventFilter(QObject* o, QEvent* e)
{
    auto widget = dynamic_cast<QWidget*>(o);
    if (widget && e->type() == QEvent::Paint) {
        if (m_backgroundImage == NewRoundRectImage) {
            QPainter painter(widget);
            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

            auto rect = widget->rect();
            QSvgRenderer svg;
            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/topLeft.svg"));
            svg.render(&painter, QRect(0, 0, 10, 10));
            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/bottomLeft.svg"));
            svg.render(&painter, QRect(0, rect.height() - 10, 10, 10));
            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/left.svg"));
            svg.render(&painter, QRect(0, 9, 10, rect.height() - 18));

            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/topRight.svg"));
            svg.render(&painter, QRect(rect.width() - 10, 0, 10, 10));
            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/bottomRight.svg"));
            svg.render(&painter, QRect(rect.width() - 10, rect.height() - 10, 10, 10));
            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/right.svg"));
            svg.render(&painter, QRect(rect.width() - 10, 9, 10, rect.height() - 18));

            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/top.svg"));
            svg.render(&painter, QRect(9, 0, rect.width() - 18, 10));
            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/center.svg"));
            svg.render(&painter, QRect(9, 9, rect.width() - 18, rect.height() - 18));
            svg.load(QString(":/com/img/BackgroundDecoration/downArrow/bottom.svg"));
            svg.render(&painter, QRect(9, rect.height() - 10, rect.width() - 18, 10));
            painter.end();
        } else {
            QPainter painter(widget);
            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

            qDrawBorderPixmap(&painter, widget->rect(), m_margins, m_backgroundImage);
        }
    }
    return QObject::eventFilter(o, e);
}

void BackgroundDecoration::setBackgorundImage(const QString& image)
{
    m_backgroundImage = image;
}

BackgroundDownArrowDecoration::BackgroundDownArrowDecoration(QWidget* decoratedWidget)
    : QObject(decoratedWidget)
{
    if (decoratedWidget)
        decoratedWidget->installEventFilter(this);
}

bool BackgroundDownArrowDecoration::eventFilter(QObject* o, QEvent* e)
{
    auto widget = dynamic_cast<QWidget*>(o);
    if (widget && e->type() == QEvent::Paint) {
        QPainter painter(widget);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

        auto rect = widget->rect();
        QSvgRenderer svg;
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/topLeft.svg"));
        svg.render(&painter, QRect(0, 0, 10, 10));
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/bottomLeft.svg"));
        svg.render(&painter, QRect(0, rect.height() - 20, 10, 10));
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/left.svg"));
        svg.render(&painter, QRect(0, 9, 10, rect.height() - 28));

        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/topRight.svg"));
        svg.render(&painter, QRect(rect.width() - 10, 0, 10, 10));
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/bottomRight.svg"));
        svg.render(&painter, QRect(rect.width() - 10, rect.height() - 20, 10, 10));
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/right.svg"));
        svg.render(&painter, QRect(rect.width() - 10, 9, 10, rect.height() - 28));

        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/top.svg"));
        svg.render(&painter, QRect(9, 0, rect.width() - 18, 10));
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/center.svg"));
        svg.render(&painter, QRect(9, 9, rect.width() - 18, rect.height() - 28));
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/bottom.svg"));
        svg.render(&painter, QRect(9, rect.height() - 20, rect.width() - 18, 10));
        svg.load(QString(":/com/img/BackgroundDecoration/downArrow/arrow.svg"));
        svg.render(&painter, QRect(rect.width() / 2 - 6, rect.height() - 20, 12, 20));
        painter.end();
    }
    return QObject::eventFilter(o, e);
}

BackgroundArrowDecoration::BackgroundArrowDecoration(QWidget* decoratedWidget, Qt::ArrowType type, bool isBlue)
    : QObject(decoratedWidget)
    , m_type(type)
{
    if (decoratedWidget)
        decoratedWidget->installEventFilter(this);
    if (isBlue)
        imagePath = ":/com/img/BackgroundDecoration/blueArrow";
    else
        imagePath = ":/com/img/BackgroundDecoration/downArrow";
}

bool BackgroundArrowDecoration::eventFilter(QObject* o, QEvent* e)
{
    auto widget = dynamic_cast<QWidget*>(o);
    if (widget && e->type() == QEvent::Paint) {
        QPainter painter(widget);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

        auto rect = widget->rect();
        QSvgRenderer svg;
        svg.load(QString("%1/topLeft.svg").arg(imagePath));
        svg.render(&painter, QRect(10, 10, 10, 10));
        svg.load(QString("%1/bottomLeft.svg").arg(imagePath));
        svg.render(&painter, QRect(10, rect.height() - 20, 10, 10));
        svg.load(QString("%1/left.svg").arg(imagePath));
        svg.render(&painter, QRect(10, 19, 10, rect.height() - 38));

        svg.load(QString("%1/topRight.svg").arg(imagePath));
        svg.render(&painter, QRect(rect.width() - 20, 10, 10, 10));
        svg.load(QString("%1/bottomRight.svg").arg(imagePath));
        svg.render(&painter, QRect(rect.width() - 20, rect.height() - 20, 10, 10));
        svg.load(QString("%1/right.svg").arg(imagePath));
        svg.render(&painter, QRect(rect.width() - 20, 19, 10, rect.height() - 38));

        svg.load(QString("%1/top.svg").arg(imagePath));
        svg.render(&painter, QRect(19, 10, rect.width() - 38, 10));
        svg.load(QString("%1/center.svg").arg(imagePath));
        svg.render(&painter, QRect(19, 19, rect.width() - 38, rect.height() - 38));
        svg.load(QString("%1/bottom.svg").arg(imagePath));
        svg.render(&painter, QRect(19, rect.height() - 20, rect.width() - 38, 10));

        if (m_type == Qt::ArrowType::LeftArrow) {
            svg.load(QString("%1/arrowLeft.svg").arg(imagePath));
            svg.render(&painter, QRect(0, rect.height() / 2 - 6, 20, 12));
        } else if (m_type == Qt::ArrowType::UpArrow) {
            svg.load(QString("%1/arrowTop.svg").arg(imagePath));
            svg.render(&painter, QRect(rect.width() / 2 - 6, 0, 12, 20));
        } else if (m_type == Qt::ArrowType::RightArrow) {
            svg.load(QString("%1/arrowRight.svg").arg(imagePath));
            svg.render(&painter, QRect(rect.width() - 20, rect.height() / 2 - 6, 20, 12));
        } else if (m_type == Qt::ArrowType::DownArrow) {
            svg.load(QString("%1/arrowBottom.svg").arg(imagePath));
            svg.render(&painter, QRect(rect.width() / 2 - 6, rect.height() - 20, 12, 20));
        }
        painter.end();
    }
    return QObject::eventFilter(o, e);
}

TipBackgroundArrowDecoration::TipBackgroundArrowDecoration(QWidget* decoratedWidget, Qt::ArrowType type, int padding)
    : QObject(decoratedWidget)
    , m_type(type)
    , m_padding(padding)
{
    if (decoratedWidget)
        decoratedWidget->installEventFilter(this);
    imagePath = ":/com/img/BackgroundDecoration/tipArrow";
}

bool TipBackgroundArrowDecoration::eventFilter(QObject* o, QEvent* e)
{
    auto widget = dynamic_cast<QWidget*>(o);
    if (widget && e->type() == QEvent::Paint) {
        QPainter painter(widget);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

        auto rect = widget->rect();
        QSvgRenderer svg;
        svg.load(QString("%1/topLeft.svg").arg(imagePath));
        svg.render(&painter, QRect(8, 8, 10, 10));
        svg.load(QString("%1/bottomLeft.svg").arg(imagePath));
        svg.render(&painter, QRect(8, rect.height() - 18, 10, 10));
        svg.load(QString("%1/left.svg").arg(imagePath));
        svg.render(&painter, QRect(8, 17, 10, rect.height() - 34));

        svg.load(QString("%1/topRight.svg").arg(imagePath));
        svg.render(&painter, QRect(rect.width() - 18, 8, 10, 10));
        svg.load(QString("%1/bottomRight.svg").arg(imagePath));
        svg.render(&painter, QRect(rect.width() - 18, rect.height() - 18, 10, 10));
        svg.load(QString("%1/right.svg").arg(imagePath));
        svg.render(&painter, QRect(rect.width() - 18, 17, 10, rect.height() - 34));

        svg.load(QString("%1/top.svg").arg(imagePath));
        svg.render(&painter, QRect(17, 8, rect.width() - 34, 10));
        svg.load(QString("%1/center.svg").arg(imagePath));
        svg.render(&painter, QRect(17, 17, rect.width() - 34, rect.height() - 34));
        svg.load(QString("%1/bottom.svg").arg(imagePath));
        svg.render(&painter, QRect(17, rect.height() - 18, rect.width() - 34, 10));

        if (m_type == Qt::ArrowType::LeftArrow) {
            svg.load(QString("%1/arrowLeft.svg").arg(imagePath));
            if (m_padding >= 0)
                svg.render(&painter, QRect(0, m_padding, 16, 16));
            else
                svg.render(&painter, QRect(0, rect.height() / 2 - 8, 16, 16));
        } else if (m_type == Qt::ArrowType::UpArrow) {
            svg.load(QString("%1/arrowTop.svg").arg(imagePath));
            if (m_padding >= 0)
                svg.render(&painter, QRect(m_padding, 0, 16, 16));
            else
                svg.render(&painter, QRect(rect.width() / 2 - 8, 0, 16, 16));
        } else if (m_type == Qt::ArrowType::RightArrow) {
            svg.load(QString("%1/arrowRight.svg").arg(imagePath));
            if (m_padding >= 0)
                svg.render(&painter, QRect(rect.width() - 16, m_padding, 16, 16));
            else
                svg.render(&painter, QRect(rect.width() - 16, rect.height() / 2 - 8, 16, 16));
        } else if (m_type == Qt::ArrowType::DownArrow) {
            svg.load(QString("%1/arrowBottom.svg").arg(imagePath));
            if (m_padding >= 0)
                svg.render(&painter, QRect(m_padding, rect.height() - 16, 16, 16));
            else
                svg.render(&painter, QRect(rect.width() / 2 - 8, rect.height() - 16, 16, 16));
        }
        painter.end();
    }
    return QObject::eventFilter(o, e);
}
