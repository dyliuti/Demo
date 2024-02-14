isEmpty(PRO_PWD): PRO_PWD = $$_PRO_FILE_PWD_
isEmpty(ROOT_PWD): ROOT_PWD = $$PWD

CONFIG += c++17

GENERATEDFILES = $$shadowed($$PRO_PWD)/GeneratedFiles
CONFIG(debug, debug|release){
    MOC_DIR = $$GENERATEDFILES/debug
    OBJECTS_DIR = $$GENERATEDFILES/debug
    UI_DIR = $$GENERATEDFILES/debug
    RCC_DIR = $$GENERATEDFILES/debug

    OUTPUT_PWD=$$shadowed($$ROOT_PWD)/qdebug
} else {
    DEFINES += QT_MESSAGELOGCONTEXT
    win32 {
        QMAKE_CXXFLAGS_RELEASE += /Zi
        QMAKE_CXXFLAGS_RELEASE += /Od
                QMAKE_CXXFLAGS_RELEASE += /MP
        QMAKE_LFLAGS_RELEASE += /DEBUG
        QMAKE_LFLAGS += /LARGEADDRESSAWARE
    }
    MOC_DIR = $$GENERATEDFILES/release
    OBJECTS_DIR = $$GENERATEDFILES/release
    UI_DIR = $$GENERATEDFILES/release
    RCC_DIR = $$GENERATEDFILES/release

# D:/Code2/Demo/Plugin/ymwPluginRelease/qrelease
    OUTPUT_PWD=$$shadowed($$ROOT_PWD)/qrelease
}

contains( DEFINES, YMW_LIBRARY ){
    win32:DESTDIR = $$OUTPUT_PWD
    macx:DESTDIR = "$$OUTPUT_PWD/$$TARGET_BUNDLE_NAME/Contents/Library"
    unix:!macx:DESTDIR = $$OUTPUT_PWD/lib
}

contains( DEFINES, YMW_PLUGIN ){
    win32:DESTDIR = $$OUTPUT_PWD/plugins
    macx:DESTDIR = "$$OUTPUT_PWD/$$TARGET_BUNDLE_NAME/Contents/Library/plugins"
    unix:!macx:DESTDIR = $$OUTPUT_PWD/plugins
}

contains( DEFINES, YMW_APP){
    win32:DESTDIR = $$OUTPUT_PWD
    macx:DESTDIR = $$OUTPUT_PWD
    unix:!macx:DESTDIR = $$OUTPUT_PWD
}

win32 {
!contains(QMAKE_TARGET.arch, x86_64) {
    target_arch = win32
    DEFINES += TARGET_ARCH_WIN32
} else {
    target_arch = win64
    DEFINES += TARGET_ARCH_WIN64
}
}

unix:!macx {
    DEFINES += BUILD_NO_CRASHHANDLER
    DEFINES += NO_APP_UPGRADE
#    DEFINES += BUILD_NO_CEF
}

# msvc: force source files to be treated as utf8 encoded
msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
