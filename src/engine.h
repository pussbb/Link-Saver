#ifndef ENGINE_H
#define ENGINE_H
#include <QDebug>
#include <QObject>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>
#include <QMap>
#include <QDir>
#include <QSettings>
#include <QFile>
#include <QMessageBox>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0, QString storeDir = "");
    QDomDocument document(const QString &name);
    QDomDocument openDocument(const QString &dir);
    QDomDocument create(const QString &name, const QString &dirName);
signals:
    
public slots:
    
private:
    QMap<QString, QDomDocument > docs;
    QString m_storeDir;
};

#endif // ENGINE_H
