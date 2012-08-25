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
  
}

Q_EXPORT_PLUGIN2(firefox, FireFoxImportPlugin);






