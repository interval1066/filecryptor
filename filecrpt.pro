QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filecrypt
TEMPLATE = app
DEFINES += "_DEBUG"
INCLUDEPATH += include

SOURCES += \
    src/aboutdlg.cpp \
    src/aes.cc \
    src/cbcmode.cc \
    src/ecbmode.cc \
    src/encryptitemmodel.cc \
    src/filecopyer.cc \
    src/main.cc \
    src/mainwindow.cc \
    src/operationmode.cc \
    src/profsdlg.cc \
    src/pwdlg.cc \
    src/rd128.cc \
    src/settings.cc

HEADERS += \
    include/aboutdlg.h \
    include/consts.h \
    include/crypto/aes.h \
    include/crypto/aesconstants.h \
    include/crypto/blockcipher.h \
    include/crypto/cbcmode.h \
    include/crypto/ecbmode.h \
    include/crypto/hexinput.h \
    include/crypto/invalidargumentexception.h \
    include/crypto/invalidkeyexception.h \
    include/crypto/operationmode.h \
    include/crypto/rd128.h \
    include/crypto/utilities.h \
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
