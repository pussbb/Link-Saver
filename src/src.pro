#-------------------------------------------------
#
# Project created by QtCreator 2012-05-20T21:09:34
#
#-------------------------------------------------

QT       += core gui xml webkit

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
    linkdialog.cpp \
    webpage.cpp \
    webcapture.cpp \
    settings.cpp \
    pictureflow/pictureflow.cpp \
    linksflow.cpp

HEADERS  += linksaver.h \
    engine.h \
    newlist.h \
    linkstree.h \
    linkdialog.h \
    webpage.h \
    webcapture.h \
    settings.h \
    pictureflow/pictureflow.h \
    linksflow.h

FORMS    += linksaver.ui \
    newlist.ui \
    linkdialog.ui \
    settings.ui

RESOURCES += \
    resource/res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/ -lPluginManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/ -lPluginManagerd
else:symbian: LIBS += -lPluginManager
else:unix: LIBS += -L$$PWD/../bin/ -lPluginManager

INCLUDEPATH += $$PWD/../lib/PluginManager
DEPENDPATH += $$PWD/../lib/PluginManager


unix:{
  QMAKE_LFLAGS += -Wl,--rpath=../bin/
  QMAKE_LFLAGS_RPATH=
}

