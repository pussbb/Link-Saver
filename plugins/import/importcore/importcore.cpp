#include "importcore.h"
#include "QDebug"

ImportCorePlugin::ImportCorePlugin()
{
}

QStringList ImportCorePlugin::dependencies() const
{
    return QStringList();
}

void ImportCorePlugin::init(QMap<QString, QObject *> dependencies, QObject *parent)
{

    Q_UNUSED(dependencies);
    m_parent = parent;
}

QWidget *ImportCorePlugin::dummyFunction()
{
    return new QDialog();
}

Q_EXPORT_PLUGIN2(importcore, ImportCorePlugin)






