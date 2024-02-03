#include "ImagePerform.h"
#include "../util/FileUtil.h"
#include <QStandardPaths>
#include <QImage>
#include <QDebug>
#include <QElapsedTimer>

static const QString s_imagePath = "C:/Users/ymw/Pictures/ymw";

void ImageTest::readImage()
{
    QElapsedTimer timer;
    timer.start(); //, "*.jpg", "*.JPG", "*.jpeg", "*.JPEG"
    auto images = FileUtil::getTypicalFiles(s_imagePath, {"*.png", "*.PNG"}, true);
    for(int i = 0; i < images.size(); ++i) {
//        if(i % 6 != 0) {
//            continue;
//        }
        QImage img(images[i]);
        qInfo() << i << img.width() << img.height();
    }
    qInfo() << "111111 elapsed: " << timer.elapsed();

    secondLoad(images);
}

void ImageTest::secondLoad(QStringList images)
{
    QElapsedTimer timer;
    timer.start();
    for(int i = 0; i < images.size(); ++i) {
//        if(i % 9 != 0) {
//            continue;
//        }
        QImage img(images[i]);
        qInfo() << i << img.width() << img.height();
    }
    qInfo() << "22222 elapsed: " << timer.elapsed();
}
