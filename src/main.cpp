#include <QtGui/QApplication>
#include "linksaver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LinkSaver w;
    w.show();
    
    return a.exec();
}
