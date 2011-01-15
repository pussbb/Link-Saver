#include "import.h"
#include "ui_import.h"
#include "QtDebug"

Import::Import(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);


}

Import::~Import()
{
    delete ui;
}
void Import::firefox_profiles()
{
    this->import_from="firefox";
#ifdef Q_OS_WIN32
    QMessageBox::warning(0, QObject::tr("System"), QObject::tr("Windows"));
#endif

#ifdef Q_OS_LINUX
   ;//(QDir::homePath()+"/.mozilla/firefox/");
    if(dir.exists(QDir::homePath()+"/.mozilla/firefox/")==false)
    {
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("It seem's to that you don't have installed Firefox!"));
        return;
    }
    else{
        if(QFile::exists(QDir::homePath()+"/.mozilla/firefox/profiles.ini")==false)
            QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Sorry but we could not find the profile of Firefox!"));
        else
        {
            QSettings settings(QDir::homePath()+"/.mozilla/firefox/profiles.ini",QSettings::IniFormat);
            int i=0;
            qDebug()<<settings.value("Profile"+QString::number(i)+"/Path","empty");
            QString path;
            while(settings.value("Profile"+QString::number(i)+"/Path",NULL)!=NULL)
            {
                if(settings.value("Profile"+QString::number(i)+"/IsRelative",1)==1)
                {
                    path=QDir::homePath()+"/.mozilla/firefox/"+settings.value("Profile"+QString::number(i)+"/Path").toString()+"/";
                }
                else
                {
                    path=settings.value("Profile"+QString::number(i)+"/Path").toString()+"/";
                }
                ui->profillist->addItem(settings.value("Profile"+QString::number(i++)+"/Name",NULL).toString(),path);

            }
        }
    }

#endif
}
#include <QFileInfoList>
void Import::on_profillist_currentIndexChanged(int index)
{
    if(this->import_from=="firefox")
    {
        if(dir.exists(ui->profillist->itemData(index).toString()+"bookmarkbackups/")==false)
        {
            QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("It seem's to that you don't have installed Firefox!"));
            return;
        }
        else
        {
            QDir bookmarkdir(ui->profillist->itemData(index).toString()+"bookmarkbackups/");
            QFileInfoList list = bookmarkdir.entryInfoList(QStringList("*.json"),QDir::Files,QDir::Time);
            if(list.size()>1)
            {
                QFileInfo fileInfo = list.at(0);
                this->build_tree(ui->profillist->itemData(index).toString()+"bookmarkbackups/"+fileInfo.fileName());
               /// qDebug()<<fileInfo.fileName();
            }

        }
       /// qDebug()<<ui->profillist->itemData(index);

    }
}

void Import::build_tree(QString file)
{
    QFile file2(file);
    if (!file2.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Could't open file for the reading"));
        return;
    }
    QTextStream stream ( &file2 );
    bool ok;
    QVariantMap result = Json::parse(stream.readAll(), ok).toMap();
    file2.close();
    if(!ok) {
        qFatal("An error occurred during parsing");
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("An error occurred during parsing"));
        return;
       // exit(1);
    }
    foreach(QVariant plugin, result["children"].toList()) {
        QVariantMap nestedMap = plugin.toMap();
        qDebug() << "\t-" <<nestedMap["title"];
       foreach(QVariant items, nestedMap["children"].toList()) {
           QVariantMap item = items.toMap();
           qDebug()<<item["title"];
            qDebug()<<item["uri"];
       }
    }
     // when your done.
 ///r  qDebug()<<result;
}
