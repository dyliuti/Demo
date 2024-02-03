TEMPLATE = subdirs

SUBDIRS += src/lib/extension \
pro_file = $$PWD/src/lib/extension/extension.pro \

SUBDIRS += src/plugin1
pro_file = $$PWD/src/plugin1/plugin1.pro

SUBDIRS += src/plugin2
pro_file = $$PWD/src/plugin2/plugin2.pro

SUBDIRS += src/extension
pro_file = $$PWD/src/extension/extension.pro

SUBDIRS += src/ymwApp
pro_file = $$PWD/src/ymwApp/ymwApp.pro


CONFIG += ordered

