#include "jsonfile.h"

JsonFile::JsonFile(QObject *parent) :
    QObject(parent)
{
}

QVariant JsonFile::readFile(const QString &fileName, const QString &codecName = "UTF-8")
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream stream ( &file );
    stream.setCodec(QTextCodec::codecForName(codecName.toLocal8Bit()));
    JsonReader reader;
    reader.parse(stream.readAll());
    if(reader.errorString().isEmpty())
        return reader.result();
    return QVariant();
}
