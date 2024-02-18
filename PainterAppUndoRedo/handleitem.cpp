#include "handleitem.h"
#include "resizablehandlerect.h"

#include <QGraphicsSceneMouseEvent>

HandleItem::HandleItem(Position position)
    : handlePosition(position)
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

void HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    ResizableHandleRect* rectItem = dynamic_cast<ResizableHandleRect*>(parentItem());
    if (rectItem == nullptr) {
        return;
    }
    QRectF rectBounds = rectItem->rectBounds();
    switch (handlePosition) {
    case TopLeft: {
        rectBounds.setTop(event->pos().y() + 6);
        rectBounds.setLeft(event->pos().x() + 6);
        break;
    }
    case TopRight: {
        rectBounds.setTop(event->pos().y() + 6);
        rectBounds.setRight(event->pos().x() - 6);
        break;
    }
    case BottomRight: {
        rectBounds.setRight(event->pos().x() - 6);
        rectBounds.setBottom(event->pos().y() - 6);
        break;
    }
    case BottomLeft: {
        rectBounds.setBottom(event->pos().y() - 6);
        rectBounds.setLeft(event->pos().x() + 6);
        break;
    }
    default:
        break;
    }

    rectItem->setRectBounds(rectBounds.normalized());
}
