TEMPLATE = subdirs
SUBDIRS = $$PWD/lib/ \ 
	  src  

# build must be last:
CONFIG += ordered

TRANSLATIONS = $$PWD/lang/qlinksaver_ru.ts \
                $$PWD/lang/qlinksaver_def.ts \
                $$PWD/lang/qlinksaver_en.ts