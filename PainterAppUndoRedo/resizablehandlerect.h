#ifndef RESIZABLEHANDLERECT_H
#define RESIZABLEHANDLERECT_H

#include "handleitem.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>

class ResizableHandleRect {
public:
    ResizableHandleRect();
    virtual ~ResizableHandleRect();

    virtual QRectF rectBounds() const = 0;
    virtual void setRectBounds(QRectF boundsRect) = 0;

    void drawHandlesIfNecessary();

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap& value);

    void setOwnerItem(QGraphicsItem* value);

private:
    void drawHandles();

private:
    QList<std::shared_ptr<HandleItem>> m_handleList;
    QGraphicsItem* m_ownerItem = nullptr;
};

#endif // RESIZABLEHANDLERECT_H
