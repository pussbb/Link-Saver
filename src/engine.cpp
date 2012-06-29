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
//    return elem;
}

void Engine::addLink(QDomElement parentNode, QVariantMap items, const QString &docName)
{

    QDomDocument doc = document(docName);

    QDomElement elem = doc.createElement("bookmark");
    elem.setAttribute("type", "link");

    if (items.contains("absoluteFileName")) {
        QString file = items.value("absoluteFileName").toString();
        items.remove("absoluteFileName");
        QString resultFile = documentDir(docName)
                + QDir::toNativeSeparators("/images/")
                + items.value("screenshort").toString();
        QFile::copy(file, resultFile);
        QFile::setPermissions(resultFile, QFile::ReadOwner | QFile::WriteOwner
                              | QFile::ExeOwner | QFile::ReadUser
                              | QFile::WriteUser | QFile::ExeUser
                              | QFile::ReadGroup | QFile::WriteGroup
                              | QFile::ExeGroup | QFile::ReadOther
                              | QFile::WriteOther | QFile::ExeOther
                             );
    }

    foreach(QString key, items.keys())
    {
        QDomElement item =doc.createElement(key);
        item.appendChild(doc.createTextNode(items.value(key).toString()));
        elem.appendChild(item);
    }
    if ( ! parentNode.isNull() )
        parentNode.appendChild(elem);
    else
        doc.documentElement().appendChild(elem);

    save(docName);
//    return elem;
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
    parentNode.removeChild(findNode(pos, parentNode));
    return save(docName);
}

