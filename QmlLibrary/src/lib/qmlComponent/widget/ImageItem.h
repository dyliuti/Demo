#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QImage>
#include <QQuickPaintedItem>

class ImageItem : public QQuickPaintedItem {
    Q_OBJECT
    Q_DISABLE_COPY(ImageItem)

public:
    explicit ImageItem(QQuickItem* parent = nullptr);
    ~ImageItem() override;

    void paint(QPainter* painter) override;

private:
    QImage m_image;
};

#endif // IMAGEITEM_H
