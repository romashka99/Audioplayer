#-------------------------------------------------
#
# Project created by QtCreator 2019-03-29T03:52:04
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AudioLibrary
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    product.cpp \
    file.cpp \
    audio.cpp \
    audiobook.cpp \
    music.cpp \
    database.cpp \
    audioform.cpp \
    audio.cpp \
    audiobook.cpp \
    file.cpp \
    music.cpp \
    product.cpp


HEADERS += \
        mainwindow.h \
    product.h \
    file.h \
    audio.h \
    audiobook.h \
    database.h \
    audioform.h \
    audio.h \
    audiobook.h \
    file.h \
    music.h \
    product.h

FORMS += \
        mainwindow.ui \
    audioform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
