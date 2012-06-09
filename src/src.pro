#-------------------------------------------------
#
# Project created by QtCreator 2012-05-20T21:09:34
#
#-------------------------------------------------

QT       += core gui xml

include(../lib/qcorewindow/qcorewindow.pri)
include(../lib/qtsingleapplication/src/qtsingleapplication.pri)

TARGET = QLinkSaver
TEMPLATE = app

unix{
    OBJECTS_DIR = ./obj/
    MOC_DIR = ./obj/
    DESTDIR = ../bin/
    UI_DIR = ./obj/
}

SOURCES += main.cpp\
        linksaver.cpp \
    engine.cpp \
    newlist.cpp \
    linkstree.cpp \
    linkdialog.cpp

HEADERS  += linksaver.h \
    engine.h \
    newlist.h \
    linkstree.h \
    linkdialog.h

FORMS    += linksaver.ui \
    newlist.ui \
    linkdialog.ui

RESOURCES += \
    resource/res.qrc
