#include "firefox.h"
#include "QDebug"
#include "QWidget"
FireFoxImportPlugin::FireFoxImportPlugin()
{
    firefoxImportAction = new QAction(tr("Firefox"), this);
    connect(firefoxImportAction, SIGNAL(triggered()), this, SLOT(open()));
    firefoxImportAction->setEnabled(appExists());
}

QStringList FireFoxImportPlugin::dependencies() const
{
    return QStringList()<<"importcore";
}

void FireFoxImportPlugin::init(QMap<QString, QObject *> dependencies, QObject *parent)
{
    QObject *obj = dependencies.value("importcore");
    bool ok = QMetaObject::invokeMethod(obj, "dummyFunction", Qt::DirectConnection,
                                  Q_RETURN_ARG(ImportDialog *, importDialog));
    if (ok)
        importDialog->show();
}

void FireFoxImportPlugin::addMenuItem(QMenu *menu)
{
    menu->addAction(firefoxImportAction);
}

void FireFoxImportPlugin::open()
{
    qDebug()<<"open import from firefox";
}

bool FireFoxImportPlugin::appExists()
{
    QDir dir(APP_DATA_PATH);
    return dir.exists();
}

Q_EXPORT_PLUGIN2(firefox, FireFoxImportPlugin)

