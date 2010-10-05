#############################################################################
# Makefile for building: LinkSaver
# Generated by qmake (2.01a) (Qt 4.7.0) on: ?? ???. 5 22:32:19 2010
# Project:  LinkSaver.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile LinkSaver.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT_LIB -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtWebKit -I/usr/include/qt4 -Iqtsingleapplication/src -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtWebKit -lQtXml -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = qtsingleapplication/src/qtsingleapplication.cpp \
		qtsingleapplication/src/qtlocalpeer.cpp \
		main.cpp \
		linksaver.cpp \
		addurl.cpp \
		pictureflow.cpp \
		about.cpp \
		apps.cpp moc_qtsingleapplication.cpp \
		moc_qtlocalpeer.cpp \
		moc_linksaver.cpp \
		moc_addurl.cpp \
		moc_pictureflow.cpp \
		moc_about.cpp \
		moc_apps.cpp \
		qrc_linkres.cpp
OBJECTS       = qtsingleapplication.o \
		qtlocalpeer.o \
		main.o \
		linksaver.o \
		addurl.o \
		pictureflow.o \
		about.o \
		apps.o \
		moc_qtsingleapplication.o \
		moc_qtlocalpeer.o \
		moc_linksaver.o \
		moc_addurl.o \
		moc_pictureflow.o \
		moc_about.o \
		moc_apps.o \
		qrc_linkres.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		qtsingleapplication/common.pri \
		qtsingleapplication/src/qtsingleapplication.pri \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		LinkSaver.pro
QMAKE_TARGET  = LinkSaver
DESTDIR       = 
TARGET        = LinkSaver

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_linksaver.h ui_addurl.h ui_about.h ui_apps.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: LinkSaver.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		qtsingleapplication/common.pri \
		qtsingleapplication/src/qtsingleapplication.pri \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtWebKit.prl \
		/usr/lib/libQtXml.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile LinkSaver.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
qtsingleapplication/common.pri:
qtsingleapplication/src/qtsingleapplication.pri:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtWebKit.prl:
/usr/lib/libQtXml.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile LinkSaver.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/LinkSaver1.0.0 || $(MKDIR) .tmp/LinkSaver1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/LinkSaver1.0.0/ && $(COPY_FILE) --parents qtsingleapplication/src/qtsingleapplication.h qtsingleapplication/src/qtlocalpeer.h linksaver.h addurl.h pictureflow.h about.h apps.h .tmp/LinkSaver1.0.0/ && $(COPY_FILE) --parents linkres.qrc .tmp/LinkSaver1.0.0/ && $(COPY_FILE) --parents qtsingleapplication/src/qtsingleapplication.cpp qtsingleapplication/src/qtlocalpeer.cpp main.cpp linksaver.cpp addurl.cpp pictureflow.cpp about.cpp apps.cpp .tmp/LinkSaver1.0.0/ && $(COPY_FILE) --parents linksaver.ui addurl.ui about.ui apps.ui .tmp/LinkSaver1.0.0/ && (cd `dirname .tmp/LinkSaver1.0.0` && $(TAR) LinkSaver1.0.0.tar LinkSaver1.0.0 && $(COMPRESS) LinkSaver1.0.0.tar) && $(MOVE) `dirname .tmp/LinkSaver1.0.0`/LinkSaver1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/LinkSaver1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_qtsingleapplication.cpp moc_qtlocalpeer.cpp moc_linksaver.cpp moc_addurl.cpp moc_pictureflow.cpp moc_about.cpp moc_apps.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_qtsingleapplication.cpp moc_qtlocalpeer.cpp moc_linksaver.cpp moc_addurl.cpp moc_pictureflow.cpp moc_about.cpp moc_apps.cpp
moc_qtsingleapplication.cpp: qtsingleapplication/src/qtsingleapplication.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) qtsingleapplication/src/qtsingleapplication.h -o moc_qtsingleapplication.cpp

moc_qtlocalpeer.cpp: qtsingleapplication/src/qtlockedfile.h \
		qtsingleapplication/src/qtlocalpeer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) qtsingleapplication/src/qtlocalpeer.h -o moc_qtlocalpeer.cpp

moc_linksaver.cpp: linksaver.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) linksaver.h -o moc_linksaver.cpp

moc_addurl.cpp: addurl.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) addurl.h -o moc_addurl.cpp

moc_pictureflow.cpp: pictureflow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) pictureflow.h -o moc_pictureflow.cpp

moc_about.cpp: about.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) about.h -o moc_about.cpp

moc_apps.cpp: apps.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) apps.h -o moc_apps.cpp

compiler_rcc_make_all: qrc_linkres.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_linkres.cpp
qrc_linkres.cpp: linkres.qrc \
		res/application-x-executable-script.png \
		LICENSE.LGPL \
		res/Blank-Map-64.png \
		res/link.png \
		res/2globe_128.png \
		res/Info-64.png
	/usr/bin/rcc -name linkres linkres.qrc -o qrc_linkres.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_linksaver.h ui_addurl.h ui_about.h ui_apps.h
compiler_uic_clean:
	-$(DEL_FILE) ui_linksaver.h ui_addurl.h ui_about.h ui_apps.h
ui_linksaver.h: linksaver.ui
	/usr/bin/uic-qt4 linksaver.ui -o ui_linksaver.h

ui_addurl.h: addurl.ui
	/usr/bin/uic-qt4 addurl.ui -o ui_addurl.h

ui_about.h: about.ui
	/usr/bin/uic-qt4 about.ui -o ui_about.h

ui_apps.h: apps.ui
	/usr/bin/uic-qt4 apps.ui -o ui_apps.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

qtsingleapplication.o: qtsingleapplication/src/qtsingleapplication.cpp qtsingleapplication/src/qtsingleapplication.h \
		qtsingleapplication/src/qtlocalpeer.h \
		qtsingleapplication/src/qtlockedfile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qtsingleapplication.o qtsingleapplication/src/qtsingleapplication.cpp

qtlocalpeer.o: qtsingleapplication/src/qtlocalpeer.cpp qtsingleapplication/src/qtlocalpeer.h \
		qtsingleapplication/src/qtlockedfile.h \
		qtsingleapplication/src/qtlockedfile.cpp \
		qtsingleapplication/src/qtlockedfile_win.cpp \
		qtsingleapplication/src/qtlockedfile_unix.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qtlocalpeer.o qtsingleapplication/src/qtlocalpeer.cpp

main.o: main.cpp linksaver.h \
		qtsingleapplication/src/qtsingleapplication.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

linksaver.o: linksaver.cpp linksaver.h \
		ui_linksaver.h \
		apps.h \
		addurl.h \
		pictureflow.h \
		about.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o linksaver.o linksaver.cpp

addurl.o: addurl.cpp addurl.h \
		ui_addurl.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o addurl.o addurl.cpp

pictureflow.o: pictureflow.cpp pictureflow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o pictureflow.o pictureflow.cpp

about.o: about.cpp about.h \
		ui_about.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o about.o about.cpp

apps.o: apps.cpp apps.h \
		ui_apps.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o apps.o apps.cpp

moc_qtsingleapplication.o: moc_qtsingleapplication.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qtsingleapplication.o moc_qtsingleapplication.cpp

moc_qtlocalpeer.o: moc_qtlocalpeer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qtlocalpeer.o moc_qtlocalpeer.cpp

moc_linksaver.o: moc_linksaver.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_linksaver.o moc_linksaver.cpp

moc_addurl.o: moc_addurl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_addurl.o moc_addurl.cpp

moc_pictureflow.o: moc_pictureflow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_pictureflow.o moc_pictureflow.cpp

moc_about.o: moc_about.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_about.o moc_about.cpp

moc_apps.o: moc_apps.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_apps.o moc_apps.cpp

qrc_linkres.o: qrc_linkres.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_linkres.o qrc_linkres.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

