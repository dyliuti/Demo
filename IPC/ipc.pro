TEMPLATE = subdirs

SUBDIRS += src/lib/ymwIPC
pro_file = $$PWD/src/lib/ymwIPC/ymwIPC.pro

SUBDIRS += src/client
pro_file = $$PWD/src/client.pro

#SUBDIRS += src/server
#pro_file = $$PWD/src/server.pro

CONFIG += ordered
