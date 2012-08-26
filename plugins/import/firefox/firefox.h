#ifndef FIREFOXIMPORTPLUGIN_H
#define FIREFOXIMPORTPLUGIN_H

#include <QtCore>
#include <QtGui>
#include <QObject>
#include <iplugin.h>
#include <ifaces.h>
#include <importdialog.h>
#include <QDir>

#ifdef Q_OS_WIN32
    #define APP_DATA_PATH getenv("APPDATA")+QDir::toNativeSeparators("\\Mozilla\\Firefox\\")
    #define CODEC_NAME "Windows-1251"
#endif
#ifdef Q_OS_OS2
    #define CODEC_NAME "UTF-8"
    #define APP_DATA_PATH QDir::homePath()+QDir::toNativeSeparators("\\Mozilla\\Firefox\\")
#endif
#ifdef Q_OS_LINUX
    #define CODEC_NAME "UTF-8"
    #define APP_DATA_PATH QDir::homePath()+QDir::toNativeSeparators("/.mozilla/firefox/")
#endif
class FireFoxImportPlugin : public QObject, IPlugin, IImport
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_INTERFACES(IImport)

public:
    explicit FireFoxImportPlugin();
    QStringList dependencies() const;
    void init(QMap<QString, QObject *> dependencies, QObject *parent);
    void addMenuItem(QMenu *menu);

public slots:
    void open();
    void currentIndexChanged(int index);
private:
    QObject *importCore;
    ImportDialog *importDialog;
    QAction *firefoxImportAction;
    QComboBox *combo;
    bool appExists();
    void initProfiles();
    void buildTree(const QVariant &data, QTreeWidgetItem *parent = NULL);
};

#endif // FIREFOXIMPORTPLUGIN_H
