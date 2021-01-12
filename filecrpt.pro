QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filecrypt
TEMPLATE = app


SOURCES += \
    src/aboutdlg.cpp \
    src/encryptitemmodel.cc \
    src/main.cc \
    src/mainwindow.cc \
    src/profsdlg.cc \
    src/pwdlg.cc \
    src/qaesencryption.cc

HEADERS += \
    include/aboutdlg.h \
    include/aesni/aesni-enc-cbc.h \
    include/aesni/aesni-enc-ecb.h \
    include/aesni/aesni-key-exp.h \
    include/encryptitemmodel.h \
    include/mainwindow.h \
    include/profile.h \
    include/profsdlg.h \
    include/pwdlg.h \
    include/qaesencryption.h

RESOURCES += \
    filrcrypt.qrc

FORMS += \
    include/aboutdlg.ui
