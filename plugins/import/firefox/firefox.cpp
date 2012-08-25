#include "firefox.h"
#include "QDebug"
#include "../importcore/importcore.h"
#include "QWidget"
FireFoxImportPlugin::FireFoxImportPlugin()
{
}

QStringList FireFoxImportPlugin::dependencies() const
{
    return QStringList()<<"importcore";
}

void FireFoxImportPlugin::init(QMap<QString, QObject *> dependencies, QObject *parent)
{
    QWidget *retVal;
    QObject *obj = dependencies.value("importcore");
    QMetaObject::invokeMethod(obj, "dummyFunction", Qt::DirectConnection,
                                  Q_RETURN_ARG(QWidget *, retVal));
    retVal->show();
}

void FireFoxImportPlugin::addMenuItem(QMenu *menu)
{
    QAction *action = new QAction(tr("Firefox"), menu);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(open()));

}

void FireFoxImportPlugin::open()
{
    qDebug()<<"open import from firefox";
}

Q_EXPORT_PLUGIN2(firefox, FireFoxImportPlugin)






