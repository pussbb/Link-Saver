#-------------------------------------------------
#
# Project created by QtCreator 2012-05-20T21:09:34
#
#-------------------------------------------------

QT       += core gui

include(../lib/qcorewindow/qcorewindow.pri)

TARGET = QLinkSaver
TEMPLATE = app

unix{
    OBJECTS_DIR = ./obj/
    MOC_DIR = ./obj/
    DESTDIR = ../bin/
    UI_DIR = ./obj/
}

SOURCES += main.cpp\
        linksaver.cpp

HEADERS  += linksaver.h \

FORMS    += linksaver.ui
