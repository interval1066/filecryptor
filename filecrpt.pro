QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filecrypt
TEMPLATE = app
DEFINES += "_DEBUG"
INCLUDEPATH += include

SOURCES += \
    src/aboutdlg.cpp \
    src/encryptitemmodel.cc \
    src/filecopyer.cc \
    src/main.cc \
    src/mainwindow.cc \
    src/profsdlg.cc \
    src/pwdlg.cc \
    src/rd128.cc \
    src/settings.cc

HEADERS += \
    include/aboutdlg.h \
    include/consts.h \
    include/crypto/rd128.h \
    include/encryptitemmodel.h \
    include/filecopyer.h \
    include/mainwindow.h \
    include/profile.h \
    include/profsdlg.h \
    include/pwdlg.h \
    include/settings.h

RESOURCES += \
    filrcrypt.qrc

FORMS += \
    include/aboutdlg.ui
