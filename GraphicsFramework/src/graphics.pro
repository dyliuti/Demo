TEMPLATE = subdirs

SUBDIRS += lib/qml
pro_file = $$PWD/src/lib/qml.pro

SUBDIRS += lib/widget
pro_file = $$PWD/src/lib/widget.pro

SUBDIRS += lib/board
pro_file = $$PWD/src/lib/board.pro

SUBDIRS += main
pro_file = $$PWD/src/main.pro

CONFIG += ordered


