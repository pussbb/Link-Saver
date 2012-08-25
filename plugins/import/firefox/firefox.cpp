#include "firefox.h"
#include "QDebug"

FireFoxImportPlugin::FireFoxImportPlugin()
{
}

QStringList FireFoxImportPlugin::dependencies() const
{
    return QStringList();
}

void FireFoxImportPlugin::init(QMap<QString, QObject *> dependencies, QObject *parent)
{

    Q_UNUSED(dependencies);
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






