
unix{
    OBJECTS_DIR = $$PWD/obj/
    MOC_DIR = $$PWD/obj/
    DESTDIR = $$PWD/../bin/plugins/
    UI_DIR = $$PWD/obj/
}

HEADERS += $$PWD/../lib/PluginManager/iplugin.h \
    $$PWD/ifaces.h

INCLUDEPATH += $$PWD \
    $$PWD/../lib/PluginManager/

DEPENDPATH += $$PWD \
    $$PWD/../lib/PluginManager/
