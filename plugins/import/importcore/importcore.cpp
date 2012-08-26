#include "importcore.h"
#include "QDebug"
#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))


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
    Q_UNUSED(parent);
    foreach(QWidget *widget, qApp->topLevelWidgets()) {
      if(widget->inherits("QMainWindow")){
          m_parent = widget;
      }
    }
}

Q_EXPORT_PLUGIN2(importcore, ImportCorePlugin)






