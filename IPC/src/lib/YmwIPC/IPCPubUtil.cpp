#include "IPCPubUtil.h"

#include <QBuffer>
#include <QJsonValue>

QPixmap IPCPubUtil::loadPixmap(QByteArray &imgArray)
{
    QPixmap pixmap;
    QBuffer buffer(&imgArray);
    buffer.open(QIODevice::ReadOnly);
    pixmap.loadFromData(imgArray, "PNG");
    return pixmap;
}

QByteArray IPCPubUtil::pixmap2ByteArray(const QPixmap &img)
{
    QByteArray pixMapData;
    QBuffer buf(&pixMapData);
    buf.open(QIODevice::WriteOnly);
    img.save(&buf, "PNG");
    buf.close();
    return pixMapData;
}

QString IPCPubUtil::base64Image(const QPixmap &img)
{
    QImage image = img.toImage();

    // 将 QImage 转换为 QByteArray，并进行 Base64 编码
    QByteArray imageBytes;
    QBuffer buffer(&imageBytes);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG"); // 可以选择不同的文件格式（如 JPEG、PNG、BMP 等）
    return imageBytes.toBase64().data();
}

QPixmap IPCPubUtil::loadPixmapBase64(const QString &base64Image)
{
    // 将 Base64 编码的数据解码为字节数组
    QByteArray imageBytes = QByteArray::fromBase64(base64Image.toUtf8());

    // 将字节数组还原为 QImage
    QImage image;
    image.loadFromData(imageBytes, "PNG"); // 使用正确的图像格式
    return QPixmap::fromImage(image);
}
