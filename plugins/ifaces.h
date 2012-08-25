#ifndef IFACES_H
#define IFACES_H

#include <QtCore>
#include <QMenu>

class IImport
{
public:
    virtual ~IImport() {};
    virtual void addMenuItem(QMenu *menu) = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(IImport,
                    "com.pussbb.LinkSaver.Plugin.IImport/0.1");
QT_END_NAMESPACE


#endif // IFACES_H
