#ifndef JSONFILE_H
#define JSONFILE_H

#include <QObject>
#include <json.h>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

class JsonFile : public QObject
{
    Q_OBJECT
public:
    explicit JsonFile(QObject *parent = 0);
    static QVariant readFile(const QString &fileName, const QString &codecName);
signals:

public slots:

};

#endif // JSONFILE_H
