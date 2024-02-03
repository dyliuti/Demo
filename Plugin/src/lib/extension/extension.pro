QT += core gui widgets

TEMPLATE = lib
TARGET = extension

CONFIG += c++17

DEFINES += YMW_LIBRARY EXTENSION_LIBRARY

win32 {
    HEADERS += $$system(for /r $$PWD %i in (*.h,*.hpp) do @echo %i)
    SOURCES += $$system(for /r $$PWD %i in (*.c,*.cpp) do @echo %i)
    FORMS += $$system(for /r $$PWD %i in (*.ui) do @echo %i)
}

include(../../../framework.pri) # must first, out_
include(../../module.pri)

# OUTPUT_PWD =  D:/Code2/Demo/Plugin/ymwPluginRelease/qrelease
# x64 D:/Code2/Demo/Plugin/ymwPluginRelease/src/lib/extension
message("111 $${_platform_type} $$shadowed($$PWD)")
INCLUDEPATH += $$PWD/..
