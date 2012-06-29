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

    QDomDocument openDocument(const QString &file);
    QDomDocument create(const QString &name, const QString &dirName);
    QString documentDir(const QString &docName) const;

    bool save(const QString &name);
    void setCurrent(const QString &name);
    void addFolder(QDomElement parentNode,const QString &name, const QString &docName);
    void addLink(QDomElement parentNode, QVariantMap items, const QString &docName);

    bool deleteDocumentFolder(const QString &docName, int pos, QDomElement parentNode);

    inline QDomElement documentRoot() const
    { return documentRoot(currentName);}

    inline QDomElement documentRoot(const QString &docName) const
    { return docs.value(docName).documentElement();}

    inline void addFolder(QDomElement parentNode,const QString &name)
    { addFolder(parentNode, name, currentName);}

    inline void addLink(QDomElement parentNode, QVariantMap items)
    { addLink(parentNode, items, currentName);}

    inline QDomNode findNode(int pos, QDomElement node)
    { return node.isNull() ? QDomNode() : node.childNodes().item(pos);}

    inline QDomNode findNode(int pos)
    { return findNode(currentName, pos);}

    inline QDomNode findNode(const QString &docName, int pos)
    { return findNode(pos, documentRoot(docName));}

    inline bool deleteDocumentFolder(int pos, QDomElement parentNode)
    { return deleteDocumentFolder(currentName, pos, parentNode);}

    inline QDomDocument document(const QString &name)
    { return docs.value(name, QDomDocument ());}
signals:
    
public slots:
    
private:
    QMap<QString, QDomDocument > docs;
    QMap<QString, QString > files;
    QString m_storeDir;
    QString currentName;
};

#endif // ENGINE_H
