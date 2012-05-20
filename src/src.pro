#-------------------------------------------------
#
# Project created by QtCreator 2012-05-20T21:09:34
#
#-------------------------------------------------

QT       += core gui

TARGET = QLinkSaver
TEMPLATE = app

unix{
    OBJECTS_DIR = ./obj/
    MOC_DIR = ./obj/
    DESTDIR = ../bin/
    UI_DIR = ./obj/
}

TRANSLATIONS = ../lang/qlinksaver_ru.ts \
                ../lang/qlinksaver_def.ts \
                ../lang/qlinksaver_en.ts

SOURCES += main.cpp\
        linksaver.cpp \
        qcorewindow.cpp

HEADERS  += linksaver.h \
	  qcorewindow.h

FORMS    += linksaver.ui
