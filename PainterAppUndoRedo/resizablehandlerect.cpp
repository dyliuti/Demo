#include "resizablehandlerect.h"
#include <QDebug>
#include <QGraphicsScene>

ResizableHandleRect::ResizableHandleRect()
{
}

ResizableHandleRect::~ResizableHandleRect()
{
}

void ResizableHandleRect::drawHandles()
{
    // Populate handles in list
    if (m_handleList.count() == 0) {
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::TopLeft));
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::TopRight));
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::BottomRight));
        m_handleList.append(std::make_shared<HandleItem>(HandleItem::BottomLeft));
    }

    // Set up pen
    QPen mPen;
    mPen.setWidth(2);
    mPen.setColor(Qt::black);

    auto func = [&](const std::shared_ptr<HandleItem>& handleItem, const QRectF& rectBound) {
        handleItem->setRect(rectBound);
        handleItem->setPen(mPen);
        handleItem->setBrush(QBrush(Qt::gray));
        m_ownerItem->scene()->addItem(handleItem.get());
        handleItem->setParentItem(m_ownerItem);
    };

    // Top left handle
    QPointF topLeftCorner
        = rectBounds().topLeft() + QPointF(-12.0, -12.0);
    auto topleftHandleRect = QRectF(topLeftCorner, QSize(12, 12));
    func(m_handleList[0], topleftHandleRect);

    // Top right
    QPointF topRightCorner = rectBounds().topRight() + QPointF(0, -12.0);
    auto topRightHandleRect = QRectF(topRightCorner, QSize(12, 12));
    func(m_handleList[1], topRightHandleRect);

    // Bottom right
    QPointF bottomRightCorner = rectBounds().bottomRight() + QPointF(0, 0);
    auto bottomRightHandleRect = QRectF(bottomRightCorner, QSize(12, 12));
    func(m_handleList[2], bottomRightHandleRect);

    // Bottom left
    QPointF bottomLeftCorner = rectBounds().bottomLeft() + QPointF(-12, 0);
    auto bottomLeftHandleRect = QRectF(bottomLeftCorner, QSize(12, 12));
    func(m_handleList[3], bottomLeftHandleRect);
}

void ResizableHandleRect::setOwnerItem(QGraphicsItem* value)
{
    m_ownerItem = value;
}

void ResizableHandleRect::drawHandlesIfNecessary()
{
    if (!m_ownerItem) {
        qWarning() << "ResizableHandleRect : No m_ownerItem set. Not drawing any\
                      handle. Please call setOwnerItem on your ResizableHandleRect subclass";
        return;
    }

    if (m_ownerItem->isSelected()) {
        drawHandles();
    } else {
        // Remove the handles
        foreach (const auto& handleItem, m_handleList) {
            m_ownerItem->scene()->removeItem(handleItem.get());
        }
        //        qDeleteAll(m_handleList);
        m_handleList.clear();
    }
}
