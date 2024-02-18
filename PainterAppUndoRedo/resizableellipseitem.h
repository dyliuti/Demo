#ifndef RESIZABLEELLIPSEITEM_H
#define RESIZABLEELLIPSEITEM_H

#include "painterapptypes.h"
#include "resizablehandlerect.h"
#include <QGraphicsRectItem>

class ResizableEllipseItem : public QGraphicsRectItem, public ResizableHandleRect {
public:
    ResizableEllipseItem();
    enum { Type = ResizableEllipseType };
    int type() const override;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    // ResizableHandleRect interface
public:
    QRectF rectBounds() const override;
    void setRectBounds(QRectF boundsRect) override;

    // QGraphicsItem interface
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
};

// Write
QDataStream& operator<<(QDataStream& out,
    const ResizableEllipseItem& mEllipse);
// Read
QDataStream& operator>>(QDataStream& in, ResizableEllipseItem& mEllipse);

#endif // RESIZABLEELLIPSEITEM_H
