#include "import.h"
#include "ui_import.h"
#include "QtDebug"

#define tmpdir QDir::toNativeSeparators (QDir::tempPath()+"/" )
#define imgdir QDir::toNativeSeparators (QApplication::applicationDirPath()+"/images/" )
Import::Import(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
    chiled=false;
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
#include <QTreeWidgetItem>
#include <QUrl>
void Import::build_tree(QString file)
{
    QFile file2(file);
    QUrl url;
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
    ui->itemsview->clear();
    foreach(QVariant plugin, result["children"].toList()) {


        QVariantMap nestedMap = plugin.toMap();
        if(!nestedMap["title"].toString().isEmpty() && nestedMap["children"].toList().size()>0)
        {
            QTreeWidgetItem *parent=new QTreeWidgetItem(ui->itemsview);
            parent->setText(0,nestedMap["title"].toString());
            parent->setIcon(0,QIcon(":folder"));
            parent->setCheckState(0,Qt::Checked);
            //// qDebug() << "\t-" <<nestedMap["title"];
            foreach(QVariant items, nestedMap["children"].toList()) {
                QVariantMap item = items.toMap();
                url.setUrl(item["uri"].toString(),QUrl::StrictMode);
                ///// qDebug()<<url.scheme();
                if(!item["title"].toString().isEmpty() && url.isValid()==true &&
                        (url.scheme()=="http" || url.scheme()=="https" || url.scheme()=="ftp"))
                {
                    QTreeWidgetItem *child=new QTreeWidgetItem(parent);
                    child->setText(0,item["title"].toString());
                    child->setCheckState(0,Qt::Checked);
                    child->setToolTip(0,item["uri"].toString());
                    child->setData(0,Qt::UserRole,item["uri"]);
                    child->setIcon(0,QIcon(":link"));
                    //// qDebug()<<item["title"];
                    ///qDebug()<<item["uri"];
                    parent->addChild(child);
                }

            }
        }

    }
    // when your done.
    ///r  qDebug()<<result;
}
#include <QFileDialog>
void Import::on_pushButton_clicked()
{
    QFileDialog::getOpenFileName(this,tr("Open Image"), "", "profiles.ini(profiles.ini)");
}

void Import::on_itemsview_itemChanged(QTreeWidgetItem* item, int column)
{
    if(item->childCount()>0 && chiled==false)
    {
        for (int i = 0; i < item->childCount(); ++i) {
            QTreeWidgetItem *child = item->child(i);
            child->setCheckState(column, item->checkState(column));
        }

    }
    else if(item->parent()!=NULL )
    {
        qDebug()<<item->parent();
        if(item->parent()->checkState(column)!=Qt::Checked && item->checkState(column)==Qt::Checked)
        {
            chiled=true;
            item->parent()->setCheckState(column,Qt::Checked);

        }

    }
    chiled=false;
}
#include<QTreeWidgetItemIterator>
// shamelessly copied from Qt Demo Browser


void Import::renderPreview(int percent)
{
    ui->image->setValue(percent);
    qDebug()<<percent;
}
void Import::saveimage()
{
    finished=true;
    QPixmap resized;
    QPixmap origin(tmpdir+fname);
    if(origin.height()>=1600){
        origin = origin.copy(0,0,origin.width(),origin.width()/1.2);// origin.scaled(origin.width()/1.4,origin.width()/1.8,Qt::IgnoreAspectRatio,Qt::FastTransformation );
    }
    resized = origin.scaled(origin.width()/1.5,origin.width()/1.9,Qt::KeepAspectRatio,Qt::FastTransformation );
    resized.save(tmpdir+fname);

    ///rui->image->setValue(percent);

}



void Import::on_pushButton_2_clicked()
{
    int i=0;
    QTreeWidgetItemIterator it(ui->itemsview);
    while (*it) {
        if ((*it)->checkState(0)==Qt::Checked && (*it)->childCount()==0)
            i++;
        ++it;
    }
    connect(&websnap.m_page, SIGNAL(loadProgress(int)), this, SLOT(renderPreview(int)));
    QObject::connect(&websnap, SIGNAL(finished()), this, SLOT(saveimage()));
    ui->itemsall->setMaximum(i);
    ui->itemsview->hide();
    ui->widget->hide();
    this->open_bookmarks();
    QTreeWidgetItemIterator items(ui->itemsview);
    while (*items) {
        if ((*items)->checkState(0)==Qt::Checked && (*items)->childCount()>0)
        {
            elem=doc.createElement("folder");
            elem.setAttribute("name",(*items)->text(0));
            doc.documentElement().appendChild(elem);
        }
        if ((*items)->checkState(0)==Qt::Checked && (*items)->childCount()==0)
        {
            ui->itemsall->setValue(ui->itemsall->value()+1);
            ui->title->setText((*items)->text(0));
            ui->curr_url->setText((*items)->data(0,Qt::UserRole).toString());
            finished=false;
            qDebug()<<(*items)->data(0,Qt::UserRole).toString().toLatin1().data();
            fname=QString(QCryptographicHash::hash((*items)->data(0,Qt::UserRole).toString().toLocal8Bit(),QCryptographicHash::Md5).toHex())+".png";
            websnap.load( guessUrlFromString( (*items)->data(0,Qt::UserRole).toString().toLatin1().data()), 100, tmpdir+fname, 1024);
            while (!finished) { qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents); }
            QFile::copy(tmpdir+fname,imgdir+fname);
            QFile::setPermissions(imgdir+fname,QFile::ReadOwner | QFile::WriteOwner |
                                  QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                  QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);

            QDomElement  element=doc.createElement("bookmark");
            element.setAttribute("url",(*items)->data(0,Qt::UserRole).toString());
            QDomText elemlText =doc.createTextNode((*items)->text(0));
            //elemlText.toElement().setAttribute();
            element.setAttribute("image",fname);
            element.appendChild(elemlText);
            elem.appendChild(element);
            //save_to_file();
        }
        ++items;
    }
    this->save_bookmarks();
}
void Import::open_bookmarks()
{
    file.setFileName(QDir::toNativeSeparators ( QApplication::applicationDirPath()+"/" ) +"links.xml");
    if(!QFile::exists(QDir::toNativeSeparators ( QApplication::applicationDirPath()+"/" ) +"links.xml"))
    {

        if(!file.open(QIODevice::WriteOnly))
        {
            ///qDebug()<<"error";
        }
        else {
            QXmlStreamWriter stream(&file);
            stream.setAutoFormatting(true);
            stream.writeStartDocument();

            stream.writeEndElement(); // bookmark
            stream.writeStartElement("lsbook");
            stream.writeAttribute("created",QDate::currentDate().toString());
            stream.writeAttribute("version","0.1");
            stream.writeEndElement(); // bookmark
            stream.writeEndDocument();
            file.close();
        }

    }
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Could't open file for the reading"));
        return;
    }
    doc.setContent(&file);
    qDebug()<<doc.toString();
    file.close();
}
void Import::save_bookmarks()
{
    file.setFileName(QDir::toNativeSeparators ( QApplication::applicationDirPath()+"/" ) +"links.xml");
    file.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream out(&file);
    doc.save(out,0);
    qDebug()<<doc.toString();
    file.close();
    this->close();
}
