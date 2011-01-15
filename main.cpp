#include <QtGui/QApplication>
#include "linksaver.h"
#include <qtsingleapplication/src/qtsingleapplication.h>
#include "QSettings"
int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);
    if (a.isRunning())
    {      a.activateWindow();
        return 0;
    }
    QSettings settings("myapp.ini", QSettings::IniFormat);
    QCoreApplication::setOrganizationName("_pussbb");
    QCoreApplication::setOrganizationDomain("krabik.co.ua");
    QCoreApplication::setApplicationName("QLinkSaver");
    LinkSaver w;
    QApplication::setQuitOnLastWindowClosed(false);
#if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5)
    w.showMaximized();
#else

    w.show();
#endif


    return a.exec();
}
