#include "ImageItem.h"
#include <QDate>
#include <QDateTime>
#include <QFontDatabase>
#include <QPainter>
#include <QTime>
#include <QTimer>

ImageItem::ImageItem(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    m_image = QImage("C:/background.png");
    //    m_image = m_image.scaled(QSize(3840, 2160), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //    m_image = m_image.scaled(QSize(1920, 1080), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

ImageItem::~ImageItem()
{
}

void ImageItem::paint(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawImage(boundingRect(), m_image);
}
