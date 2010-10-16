#include <QtGui/QApplication>
#include "linksaver.h"
#include <QTranslator>
#if !defined(Q_OS_OS2)
#include <qtsingleapplication/src/qtsingleapplication.h>
#endif
int main(int argc, char *argv[])
{

#if !defined(Q_OS_OS2)
    QtSingleApplication a(argc, argv);
    if (a.isRunning())
    {      a.activateWindow();
        return 0;
    }
#else
    QApplication a(argc, argv);
#endif
    LinkSaver w;
    QString locale = QLocale::system().name();
    QTranslator translator;
    if(locale.length()>2)
    {
        locale.resize(2);
    }
    translator.load(QDir::toNativeSeparators (QApplication::applicationDirPath()+"/lang/" )+"linksaver_"+locale);
    QApplication::installTranslator(&translator);
    QApplication::setQuitOnLastWindowClosed(false);
#if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5)
    w.showMaximized();
#else

    w.show();
#endif


    return a.exec();
}
