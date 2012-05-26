#include <QtGui/QApplication>
#include "linksaver.h"

#include <../lib/qtsingleapplication/src/qtsingleapplication.h>
#include "QSettings"

int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);
    if (a.isRunning())
    {
        a.activateWindow();
        return 0;
    }

    QCoreApplication::setOrganizationName("_pussbb");
    QCoreApplication::setOrganizationDomain("krabik.co.ua");
    QCoreApplication::setApplicationName("QLinkSaver");
    QApplication::setApplicationName("QLinkSaver");
    QApplication::setApplicationVersion("2.5.1.5");
    QApplication::setQuitOnLastWindowClosed(false);
    LinkSaver w;

    QSettings settings;
    if( settings.value("hideonstart",false) == false)
        w.show();

    return a.exec();
}
