#-------------------------------------------------
#
# Project created by QtCreator 2010-03-28T14:54:17
#
#-------------------------------------------------

QT       += core gui xml webkit network
include(qtsingleapplication/src/qtsingleapplication.pri)
TARGET = LinkSaver
TEMPLATE = app
win32 {
   RC_FILE = win2.rc
}
TRANSLATIONS = ./lang/linksaver_ru.ts \
                ./lang/linksaver_def.ts \
                ./lang/linksaver_en.ts

SOURCES += main.cpp\
        linksaver.cpp \
    addurl.cpp \
    pictureflow.cpp \
    about.cpp \
    apps.cpp \
    settings.cpp

HEADERS  += linksaver.h \
    addurl.h \
    pictureflow.h \
    about.h \
    apps.h \
    settings.h

FORMS    += linksaver.ui \
    addurl.ui \
    about.ui \
    apps.ui \
    settings.ui

RESOURCES += \
    linkres.qrc

OTHER_FILES += \
    README
