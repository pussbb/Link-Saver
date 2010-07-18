#-------------------------------------------------
#
# Project created by QtCreator 2010-03-28T14:54:17
#
#-------------------------------------------------

QT       += core gui xml webkit network

TARGET = LinkSaver
TEMPLATE = app
win32 {
   RC_FILE = win2.rc
}
include(qtsingleapplication/src/qtsingleapplication.pri)
SOURCES += main.cpp\
        linksaver.cpp \
    addurl.cpp \
    pictureflow.cpp \
    about.cpp

HEADERS  += linksaver.h \
    addurl.h \
    pictureflow.h \
    about.h

FORMS    += linksaver.ui \
    addurl.ui \
    about.ui

RESOURCES += \
    linkres.qrc
