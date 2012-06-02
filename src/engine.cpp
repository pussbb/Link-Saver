#include "engine.h"

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    QSettings settings;

    ///QString defaultDirName = QApplication::applicationDirPath()+QDir::toNativeSeparators("/data/");
    QString dirName = settings.value("storeengine.dir", "").toString();

}

void Engine::openDocument(const QString &name)
{
    currentName = name;
}

QDomDocument Engine::document(const QString &name)
{
    return docs.value(name, QDomDocument ());
}

