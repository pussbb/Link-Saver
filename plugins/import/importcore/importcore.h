#ifndef FIREFOXIMPORTPLUGIN_H
#define FIREFOXIMPORTPLUGIN_H

#include <QtCore>
#include <QtGui>
#include <QObject>
#include <iplugin.h>


class ImportCorePlugin : public QObject, IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)

public:
    explicit ImportCorePlugin();
    QStringList dependencies() const;
    void init(QMap<QString, QObject *> dependencies, QObject *parent);
public slots:
    QWidget * dummyFunction();
private:
    QObject *m_parent;
};

#endif // FIREFOXIMPORTPLUGIN_H
