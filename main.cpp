#include <QtGui/QApplication>
#include "linksaver.h"
#include <qtsingleapplication/src/qtsingleapplication.h>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);
    LinkSaver w;
   // CreateMutex(0, true, "your_appname_start_once");
   // if (GetLastError() == ERROR_ALREADY_EXISTS) exit(0);
    if (a.isRunning())
    {      a.activateWindow();
        return 0;
    }
    QString locale = QLocale::system().name();
QTranslator translator;
translator.load(QDir::toNativeSeparators (QApplication::applicationDirPath()+"/lang/" )+"linksaver_"+locale);
a.installTranslator(&translator);
       QApplication::setQuitOnLastWindowClosed(false);
#if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5)
    w.showMaximized();
#else

    w.show();
#endif


    return a.exec();
}
