#include "engine.h"

Engine::Engine(QObject *parent, QString storeDir) :
    QObject(parent),
    m_storeDir(storeDir)
{
}

QDomDocument Engine::openDocument(const QString &dir)
{
    QFile f (dir + QDir::toNativeSeparators("/links.xml"));
    f.open(QIODevice::Text | QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(&f);
    f.close();
    qDebug()<<doc.toString();
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
    stream.writeAttribute("version","0.1");
    stream.writeAttribute("name", name);
    stream.writeEndElement();
    stream.writeEndDocument();
    f.close();
    return openDocument(dirName);
}

QDomDocument Engine::document(const QString &name)
{
    return docs.value(name, QDomDocument ());
}

