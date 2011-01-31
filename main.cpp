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
    QCoreApplication::setOrganizationName("_pussbb");
    QCoreApplication::setOrganizationDomain("krabik.co.ua");
    QCoreApplication::setApplicationName("QLinkSaver");
    QApplication::setApplicationName("QLinkSaver");
    QApplication::setApplicationVersion("2.1.1.5");
    LinkSaver w;
    QApplication::setQuitOnLastWindowClosed(false);
#if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5)
    w.showMaximized();
#else
    QSettings settings;
    if(settings.value("hideonstart",false)==false)
        w.show();
#endif
    return a.exec();
}
