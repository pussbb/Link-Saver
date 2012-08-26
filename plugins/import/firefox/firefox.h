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
#endif
#ifdef Q_OS_OS2
     #define APP_DATA_PATH QDir::homePath()+QDir::toNativeSeparators("\\Mozilla\\Firefox\\")
#endif
#ifdef Q_OS_LINUX
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
private:
    ImportDialog *importDialog;
    QAction *firefoxImportAction;
    bool appExists();
};

#endif // FIREFOXIMPORTPLUGIN_H
