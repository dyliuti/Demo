#ifndef RESIZABLESTARITEM_H
#define RESIZABLESTARITEM_H

#include "painterapptypes.h"
#include "resizablehandlerect.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneDragDropEvent>

class ResizableStarItem : public QGraphicsRectItem, public ResizableHandleRect {
public:
    explicit ResizableStarItem();
    enum { Type = ResizableStarType };
    int type() const override;

    QRectF rectBounds() const override;
    void setRectBounds(QRectF boundsRect) override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPainterPath starFromRect(QRectF mRectF);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
};

// Write
QDataStream& operator<<(QDataStream& out,
    const ResizableStarItem& mStar);

// Read
QDataStream& operator>>(QDataStream& in, ResizableStarItem& mStar);

#endif // RESIZABLESTARITEM_H
