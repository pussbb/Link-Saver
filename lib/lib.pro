TEMPLATE = subdirs
SUBDIRS = $$PWD/qcorewindow/ \
	  $$PWD/PluginManager
 

# build must be last:
CONFIG += ordered 
