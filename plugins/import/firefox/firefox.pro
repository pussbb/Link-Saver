QT += core gui

include(../../commonplugin.pri)
include(../import.pri)

TARGET = firefox
TEMPLATE = lib
CONFIG += plugin

SOURCES += firefox.cpp \
    importdialog.cpp

HEADERS += firefox.h \
    importdialog.h



