#ifndef EEOIPCPUBUTIL_H
#define EEOIPCPUBUTIL_H

#include <QPixmap>
#include <QByteArray>
#include "ymwIPC_global.h"

namespace IPCPubUtil {

YMWIPC_EXPORT QPixmap loadPixmap(QByteArray &imgArray);
YMWIPC_EXPORT QByteArray pixmap2ByteArray(const QPixmap &img);

YMWIPC_EXPORT QString base64Image(const QPixmap &img);
YMWIPC_EXPORT QPixmap loadPixmapBase64(const QString &base64Image);

}

#endif // EEOIPCPUBUTIL_H
