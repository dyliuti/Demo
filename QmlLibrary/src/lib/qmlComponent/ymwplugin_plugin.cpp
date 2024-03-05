#include "ymwplugin_plugin.h"

#include "widget/DateTimeItem.h"
#include "widget/ImageItem.h"
#include "widget/myitem.h"
#include <qqml.h>

void YmwPluginPlugin::registerTypes(const char* uri)
{
    // @uri ymwComponent
    qmlRegisterType<MyItem>(uri, 1, 0, "MyItem");
    qmlRegisterType<DateTimeItem>(uri, 1, 0, "DateTimeItem");
    qmlRegisterType<ImageItem>(uri, 1, 0, "ImageItem");
    qmlRegisterType(QUrl("qrc:/qml/qml/com/ComButton.qml"), uri, 1, 0, "ComButton");
    qmlRegisterType(QUrl("qrc:/qml/qml/com/ComImage.qml"), uri, 1, 0, "ComImage");
    qmlRegisterType(QUrl("qrc:/qml/qml/com/ComText.qml"), uri, 1, 0, "ComText");
}
