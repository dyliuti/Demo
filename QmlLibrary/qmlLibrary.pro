TEMPLATE = subdirs

SUBDIRS += src/lib/qmlComponent \

pro_file = $$PWD/src/lib/qmlComponent/qmlComponent.pro

SUBDIRS += src/qmlApp
pro_file = $$PWD/src/quickApp/qmlApp.pro

SUBDIRS += src/quickWidgetApp
pro_file = $$PWD/src/quickWidgetApp/quickWidgetApp.pro

CONFIG += ordered

