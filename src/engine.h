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
    enum LinkAttribute{ Url, Title, Screenshort};
    enum documentElement{Nothing, Link, Folder};
    Q_DECLARE_FLAGS(LinkAttributes, LinkAttribute)
    Q_DECLARE_FLAGS(documentElements, documentElement)
    QDomDocument openDocument(const QString &file);
    QDomDocument create(const QString &name, const QString &dirName);
    QString documentDir(const QString &docName) const;

    bool save(const QString &name);
    void setCurrent(const QString &name);
    void addFolder(QDomElement parentNode,const QString &name, const QString &docName);
    void addLink(QDomElement parentNode, QVariantMap items, const QString &docName);
    void moveItem(QDomElement toNode, QDomElement node, const QString &docName);



    bool deleteDocumentFolder(const QString &docName, int pos, QDomElement parentNode);
    bool deleteDocumentLink(const QString &docName, int pos, QDomElement parentNode);

    static Engine::documentElement nodeType(QDomNode node);
    static QString nodeData(QDomNode node, Engine::LinkAttribute attr);


    inline bool save()
    { return save(currentName);}

    inline QString documentDir() const
    { return documentDir(currentName);}

    inline void moveItem(QDomElement toNode, QDomElement node)
    { moveItem(toNode, node, currentName);}

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

    inline bool deleteDocumentLink(int pos, QDomElement parentNode)
    { return deleteDocumentLink(currentName, pos, parentNode);}



    inline QDomDocument document(const QString &name)
    { return docs.value(name, QDomDocument ());}

    inline QString documentImagesPath(const QString &docName) const
    { return documentDir(docName) + QDir::toNativeSeparators("/images/");}

    inline QString documentImagesPath() const
    { return documentImagesPath(currentName);}

signals:

public slots:

private:
    QMap<QString, QDomDocument > docs;
    QMap<QString, QString > files;
    QString m_storeDir;
    QString currentName;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Engine::documentElements)
Q_DECLARE_OPERATORS_FOR_FLAGS(Engine::LinkAttributes)
#endif // ENGINE_H
