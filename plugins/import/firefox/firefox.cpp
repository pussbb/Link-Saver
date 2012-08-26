#include "firefox.h"
#include "QDebug"
#include "QWidget"
#include <QSettings>
#include <jsonfile.h>

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
    Q_UNUSED(parent);
    importCore = dependencies.value("importcore");
}

void FireFoxImportPlugin::addMenuItem(QMenu *menu)
{
    menu->addAction(firefoxImportAction);
}

void FireFoxImportPlugin::open()
{
    bool ok = QMetaObject::invokeMethod(importCore, "dialog", Qt::DirectConnection,
                                  Q_RETURN_ARG(ImportDialog *, importDialog));
    if ( ! ok)
        return;

    combo = importDialog->getProfileList();
    connect(combo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(currentIndexChanged(int)));
    initProfiles();
    importDialog->exec();
    importDialog->deleteLater();
}

#include <QFileInfoList>
void FireFoxImportPlugin::currentIndexChanged(int index)
{

    QDir bookmarkdir(combo->itemData(index).toString()+QDir::toNativeSeparators("bookmarkbackups/"));
    QFileInfoList list = bookmarkdir.entryInfoList(QStringList("*.json"),
                                                     QDir::Files,
                                                        QDir::Time);
    if(list.size() > 1)
    {
        QFileInfo fi = list.at(0);
        importDialog->clearData();
        buildTree(JsonFile::readFile(fi.absoluteFilePath(), CODEC_NAME));
    }
}

bool FireFoxImportPlugin::appExists()
{
    QDir dir(APP_DATA_PATH);
    return dir.exists();
}

void FireFoxImportPlugin::initProfiles()
{
    QSettings settings(APP_DATA_PATH+"profiles.ini", QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName(CODEC_NAME));

    QStringList groups = settings.childGroups();
    QString path;
    foreach(const QString &profile, groups.filter("Profile"))
    {
        settings.beginGroup(profile);
        path = settings.value("Path").toString()+QDir::toNativeSeparators("/");
        if(settings.value("IsRelative", true).toBool())
            path = APP_DATA_PATH+path;
        combo->addItem(settings.value("Name","default").toString(),path);
        settings.endGroup();
    }

    return;
}

void FireFoxImportPlugin::buildTree(const QVariant &data, QTreeWidgetItem *parent)
{
    QString title;
    QString url;
    foreach(QVariant plugin, data.toMap().value("children").toList()) {
        QVariantMap nestedMap = plugin.toMap();
        title = nestedMap.value("title").toString();
        url = nestedMap.value("uri").toString();
        if (nestedMap.contains("children")
                && nestedMap.value("children").toList().count() > 0)
        {
            buildTree(nestedMap, importDialog->appendItem(title,url,true,parent));
        }
        else {
            importDialog->appendItem(title,url,false,parent);
        }

    }
}

Q_EXPORT_PLUGIN2(firefox, FireFoxImportPlugin)

