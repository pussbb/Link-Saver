QT += core gui

include(../../commonplugin.pri)
include(../../coreapp.pri)

TARGET = importcore
TEMPLATE = lib
CONFIG += plugin

SOURCES += importcore.cpp \
    importdialog.cpp

HEADERS += importcore.h \
    importdialog.h

FORMS += \
    importdialog.ui



