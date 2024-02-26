#include "ymwplugin_plugin.h"

#include "widget/myitem.h"
#include <qqml.h>
#include <widget/DateTimeItem.h>

void YmwPluginPlugin::registerTypes(const char* uri)
{
    // @uri ymwComponent
    qmlRegisterType<MyItem>(uri, 1, 0, "MyItem");
    qmlRegisterType<DateTimeItem>(uri, 1, 0, "DateTimeItem");
    qmlRegisterType(QUrl("qrc:/qml/qml/com/ComButton.qml"), uri, 1, 0, "ComButton");
    qmlRegisterType(QUrl("qrc:/qml/qml/com/ComImage.qml"), uri, 1, 0, "ComImage");
    qmlRegisterType(QUrl("qrc:/qml/qml/com/ComText.qml"), uri, 1, 0, "ComText");
}
