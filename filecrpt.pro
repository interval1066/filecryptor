QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filecrypt
TEMPLATE = app
DEFINES += "_DEBUG"
INCLUDEPATH += include

SOURCES += \
    src/aboutdlg.cpp \
    src/aes256.cc \
    src/aes256_base.cc \
    src/aes256_prng.cc \
    src/encryptitemmodel.cc \
    src/filecopyer.cc \
    src/main.cc \
    src/mainwindow.cc \
    src/profsdlg.cc \
    src/pwdlg.cc \
    src/rd128.cc \
    src/s_box.cc \
    src/settings.cc

HEADERS += \
    include/aboutdlg.h \
    include/consts.h \
    include/crypto/aes256.h \
    include/crypto/aes256_base.h \
    include/crypto/aes256_prng.h \
    include/crypto/byte_block.h \
    include/crypto/padding_type.h \
    include/crypto/rd128.h \
    include/crypto/s_box.h \
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
