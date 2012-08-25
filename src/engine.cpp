#include "engine.h"

Engine::Engine(QObject *parent, QString storeDir) :
    QObject(parent),
    m_storeDir(storeDir)
{
}

QDomDocument Engine::openDocument(const QString &file)
{
    QFile f (file);
    f.open(QIODevice::Text | QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(&f);
    f.close();
    QString name =  doc.documentElement().attribute("name");
    docs.insert(name, doc);
    files.insert(name, file);
    return doc;
}

QDomDocument Engine::create(const QString &name, const QString &dirName)
{
    QFile f(dirName + QDir::toNativeSeparators("/links.xml"));
    if( ! f.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0,  QObject::tr("Directory write protected"),
                             QObject::tr("%1\nPlease choose another directory.")
                             .arg(f.fileName()));
        return QDomDocument();
    }

    QXmlStreamWriter stream(&f);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeEndElement(); // bookmark
    stream.writeStartElement("lsbook");
    stream.writeAttribute("created", QDate::currentDate().toString());
    stream.writeAttribute("version","1.1");
    stream.writeAttribute("name", name);
    stream.writeEndElement();
    stream.writeEndDocument();
    f.close();
    return openDocument(f.fileName());
}

void Engine::setCurrent(const QString &name)
{
    if (docs.contains(name))
        currentName = name;
    else
        currentName = "";
}

void Engine::moveItem(QDomElement toNode, QDomElement node, const QString &docName)
{
    toNode.appendChild(node);
    save(docName);
}


void Engine::addFolder(QDomElement parentNode, const QString &name, const QString &docName)
{
    QDomDocument doc = document(docName);
    QDomElement elem = doc.createElement("folder");
    elem.setAttribute("name", name);

    if ( ! parentNode.isNull() )
        parentNode.appendChild(elem);
    else
        doc.documentElement().appendChild(elem);

    save(docName);
}

void Engine::addLink(QDomElement parentNode, QVariantMap items, const QString &docName)
{

    QDomDocument doc = document(docName);

    QDomElement elem = doc.createElement("bookmark");
    elem.setAttribute("type", "link");

    if (items.contains("absoluteFileName")) {
        QString file = items.value("absoluteFileName").toString();
        items.remove("absoluteFileName");
        QString resultFile = documentImagesPath(currentName) + items.value("screenshort").toString();
        copyImage(file, resultFile);
    }

    foreach(QString key, items.keys())
    {
        QDomElement item = doc.createElement(key);
        item.appendChild(doc.createTextNode(items.value(key).toString()));
        elem.appendChild(item);
    }

    if ( ! parentNode.isNull() )
        parentNode.appendChild(elem);
    else
        doc.documentElement().appendChild(elem);

    save(docName);
}

void Engine::updateLink(QDomElement element, QVariantMap items, const QString &docName)
{
    if (items.contains("absoluteFileName")) {
        QString file = items.value("absoluteFileName").toString();
        items.remove("absoluteFileName");
        QString resultFile = documentImagesPath(currentName) + items.value("screenshort").toString();
        copyImage(file, resultFile);
    }

    foreach(QString key, items.keys())
    {
        element.firstChildElement(key).firstChild().setNodeValue(items.value(key).toString());
    }
    save(docName);
}

bool Engine::save(const QString &name)
{

    QFile f (files.value(name,""));
    if ( ! f.open(QIODevice::Text | QIODevice::WriteOnly))
        return false;
    QTextStream out(&f);
    out.setCodec("UTF-8");
    document(name).save(out, 4);
    f.close();
    return true;
}

QString Engine::documentDir(const QString &docName) const
{
    QString file = files.value(docName);
    if ( file.isNull())
        return QString();
    QFileInfo fi(file);
    return fi.absolutePath();
}

bool Engine::deleteDocumentFolder(const QString &docName, int pos, QDomElement parentNode)
{
    QDomNode node = findNode(pos, parentNode);
    for(int i = 0; i > node.childNodes().count(); ++i) {
        QDomNode _node = node.childNodes().at(i);
        if ( _node.nodeName() == "folder")
        {
            deleteDocumentFolder(docName, pos, _node.toElement());
        }
        if ( _node.nodeName() == "bookmark"
             && _node.toElement().attribute("type") == "link") {
            deleteDocumentLink(docName, pos, _node.toElement());
        }
    }
    parentNode.removeChild(node);
    return save(docName);
}

bool Engine::deleteDocumentLink(const QString &docName, int pos, QDomElement parentNode)
{
    QDomNode node = findNode(pos, parentNode);
    QString file = documentImagesPath(docName) + Engine::nodeData(node, Engine::Screenshort);

    QFile::remove(file);

    parentNode.removeChild(node);
    return save(docName);
}

QString Engine::nodeData(QDomNode node, Engine::LinkAttribute attr){
    switch(attr){
        case Engine::Title :
            if (Engine::nodeType(node) == Engine::Folder)
                return node.toElement().attribute("name");
            return node.firstChildElement("title").toElement().text();
        case Engine::Url:
            return node.firstChildElement("url").toElement().text();
        case Engine::Screenshort:
            return node.firstChildElement("screenshort").toElement().text();
        default:
            return QString();
    }
}

void Engine::copyImage(const QString &image, const QString &fileName)
{

    if (QFile::exists(fileName))
    {
        QFile::remove(fileName);
    }
    QFile::copy(image, fileName);
    QFile::setPermissions(fileName, QFile::ReadOwner | QFile::WriteOwner
                          | QFile::ExeOwner | QFile::ReadUser
                          | QFile::WriteUser | QFile::ExeUser
                          | QFile::ReadGroup | QFile::WriteGroup
                          | QFile::ExeGroup | QFile::ReadOther
                          | QFile::WriteOther | QFile::ExeOther
                         );
}

Engine::documentElement Engine::nodeType(QDomNode node)
{
    if (node.nodeName() == "folder")
        return Engine::Folder;
    if ( node.nodeName() == "bookmark"
         && node.toElement().attribute("type") == "link")
        return Engine::Link;
    return Engine::Nothing;
}
