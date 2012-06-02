#ifndef ENGINE_H
#define ENGINE_H
#include <QDebug>
#include <QObject>
///#include <QtXml/QtXml>
#include <QtXml/QDomDocument>
#include <QMap>
#include <QDir>
#include <QSettings>


class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
    inline QDomDocument document(const QString &name) { return docs.value(name, QDomDocument ());}
    void openDocument(const QString &name);
signals:
    
public slots:
    
private:
    QMap<QString, QDomDocument > docs;
    QString currentName;
    QString storeDir;
};

#endif // ENGINE_H
