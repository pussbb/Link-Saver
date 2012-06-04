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
    QDomDocument openDocument(const QString &file);
    QDomDocument create(const QString &name, const QString &dirName);
    ///void updateDocument(const QString &name, const QDomDocument &doc);
    QDomElement documentRoot() const;
    QDomElement documentRoot(const QString &docName) const;
    void setCurrent(const QString &name);
    void addFolder(const QString &name);
    void addFolder(const QString &name, const QString &docName);
    bool save(const QString &name);
signals:
    
public slots:
    
private:
    QMap<QString, QDomDocument > docs;
    QMap<QString, QString > files;
    QString m_storeDir;
    QString currentName;
};

#endif // ENGINE_H
