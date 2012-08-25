#ifndef FIREFOXIMPORTPLUGIN_H
#define FIREFOXIMPORTPLUGIN_H

#include <QtCore>
#include <QtGui>
#include <QObject>
#include <iplugin.h>
#include <ifaces.h>


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
};

#endif // FIREFOXIMPORTPLUGIN_H
