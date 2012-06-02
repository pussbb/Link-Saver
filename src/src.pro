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
    engine.cpp

HEADERS  += linksaver.h \
    engine.h

FORMS    += linksaver.ui
