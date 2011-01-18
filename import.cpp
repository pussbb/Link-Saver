#include "import.h"
#include "ui_import.h"
#include "QtDebug"

#define tmpdir QDir::toNativeSeparators (QDir::tempPath()+QDir::toNativeSeparators("/") )
#define imgdir QDir::toNativeSeparators (QApplication::applicationDirPath()+QDir::toNativeSeparators("/images/") )
Import::Import(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
    chiled=false;
    ui->abort->hide();
}

Import::~Import()
{
    delete ui;
}
void Import::firefox_profiles()
{
    this->import_from="firefox";
    manual=false;
#ifdef Q_OS_WIN32
    QString appdata=getenv("APPDATA");
    if(dir.exists(appdata+"\\Mozilla\\Firefox\\")==false)
    {
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("It seem's to that you don't have installed Firefox!"));
        return;
    }
    else{
        if(QFile::exists(appdata+"\\Mozilla\\Firefox\\"+"profiles.ini")==false)
            QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Sorry but we could not find the profile of Firefox!"));
        else
        {
            QSettings settings(appdata+"\\Mozilla\\Firefox\\"+"profiles.ini",QSettings::IniFormat);
            int i=0;
            qDebug()<<settings.value("Profile"+QString::number(i)+"/Path","empty");
            QString path;
            while(settings.value("Profile"+QString::number(i)+"/Path",NULL)!=NULL)
            {
                if(settings.value("Profile"+QString::number(i)+"/IsRelative",1)==1)
                {
                    path=appdata+"\\Mozilla\\Firefox\\"+settings.value("Profile"+QString::number(i)+"/Path").toString()+"/";
                }
                else
                {
                    path=settings.value("Profile"+QString::number(i)+"/Path").toString()+"/";
                }            ///QDir bookmarkdir(ui->profillist->itemData(index).toString()+"bookmarkbackups/");
                ui->profillist->addItem(settings.value("Profile"+QString::number(i++)+"/Name",NULL).toString(),path);

            }
        }
    }
#endif

#ifdef Q_OS_LINUX
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
    if(this->import_from=="firefox" && !manual)
    {
        QDir bookmarkdir(ui->profillist->itemData(index).toString()+QDir::toNativeSeparators("bookmarkbackups/"));
        if(bookmarkdir.exists(bookmarkdir.path())==false)
        {
            QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("It seem's to that you don't have installed Firefox!"));
            return;
        }
        else
        {
            QFileInfoList list = bookmarkdir.entryInfoList(QStringList("*.json"),QDir::Files,QDir::Time);
            if(list.size()>1)
            {
                QFileInfo fileInfo = list.at(0);
                this->build_tree(bookmarkdir.canonicalPath()+QDir::toNativeSeparators("/")+fileInfo.fileName());
            }

        }
    }
    else if(import_from=="chromium")
    {
        this->build_tree(ui->profillist->itemData(index).toString());
    }
}
void Import::chromium_bookmaks()
{
    import_from="chromium";
    manual=false;
    QString chromium_path;

#ifdef Q_OS_WIN32
    chromium_path=getenv("LOCALAPPDATA");
    chromium_path+="\\Chromium\\User Data\\Default\\";
#endif

#ifdef Q_OS_LINUX
    chromium_path=QDir::homePath()+"/.config/chromium/Default/";
#endif
    if(dir.exists(chromium_path)==false)
    {
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("It seem's to that you don't have installed Chromium!"));
        return;
    }
    else{
        if(QFile::exists(chromium_path+"Bookmarks")==false)
            QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Sorry but we could not find the profile of Chromium!"));
        else
            ui->profillist->addItem("Default",chromium_path+"Bookmarks");
    }
}

#include <QTreeWidgetItem>
#include <QUrl>
void Import::build_tree(QString file)
{
    QFile file2(file);

    if (!file2.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("Could't open file for the reading"));
        return;
    }
    QTextStream stream ( &file2 );
    stream.setCodec("UTF-8");
    bool ok;
    QVariantMap result = Json::parse(stream.readAll(), ok).toMap();
    file2.close();
    if(!ok) {
        qFatal("An error occurred during parsing");
        QMessageBox::warning(0, QObject::tr("Error"), QObject::tr("An error occurred during parsing"));
        return;
    }
    ui->itemsview->clear();
    if(import_from=="firefox")
        this->firefox_json(result);
    else if(import_from=="chromium")
    {
        this->chromium_json(result["roots"].toMap(),"bookmark_bar",tr("Boormark bar"));
        this->chromium_json(result["roots"].toMap(),"other",tr("Other Boormark"));
    }
}
void Import::chromium_json(QVariantMap result,QString section,QString name)
{
    foreach(QVariant root, result[section].toMap()) {
        QList<QVariant > items = root.toList();
        if(items.size()>0)
        {
            QTreeWidgetItem *parent=new QTreeWidgetItem(ui->itemsview);
            parent->setText(0,name);
            parent->setIcon(0,QIcon(":folder"));
            parent->setCheckState(0,Qt::Checked);
            for (int i = 0; i < items.size(); ++i) {
                QVariantMap map=items.at(i).toMap();
                if(map["type"].toString()=="folder")
                {
                    chromium_json(items.at(i),"children",map["name"].toString());
                }
                else if (map["type"].toString()=="url") {
                    QTreeWidgetItem *child=new QTreeWidgetItem(parent);
                    child->setText(0,map["name"].toString());
                    child->setCheckState(0,Qt::Checked);
                    child->setToolTip(0,map["url"].toString());
                    child->setData(0,Qt::UserRole,map["url"]);
                    child->setIcon(0,QIcon(":link"));
                    parent->addChild(child);
                }
            }
        }


    }
}
void Import::chromium_json(QVariant result,QString section,QString name)
{

    QList<QVariant > items = result.toMap()[section].toList();
    if(items.size()>0)
    {
        QTreeWidgetItem *parent=new QTreeWidgetItem(ui->itemsview);
        parent->setText(0,name);
        parent->setIcon(0,QIcon(":folder"));
        parent->setCheckState(0,Qt::Checked);
        for (int i = 0; i < items.size(); ++i) {
            ////if (items.at(i))
            QVariantMap map=items.at(i).toMap();
            if(map["type"].toString()=="folder")
            {
                chromium_json(items.at(i).toList(),"children",map["name"].toString());
            }
            else if (map["type"].toString()=="url") {
                QTreeWidgetItem *child=new QTreeWidgetItem(parent);
                child->setText(0,map["name"].toString());
                child->setCheckState(0,Qt::Checked);
                child->setToolTip(0,map["url"].toString());
                child->setData(0,Qt::UserRole,map["url"]);
                child->setIcon(0,QIcon(":link"));
                parent->addChild(child);
            }
        }
    }

}
void Import::firefox_json(QVariantMap result)
{
    QUrl url;
    foreach(QVariant plugin, result["children"].toList()) {
        QVariantMap nestedMap = plugin.toMap();
        if(!nestedMap["title"].toString().isEmpty() && nestedMap["children"].toList().size()>0)
        {
            QTreeWidgetItem *parent=new QTreeWidgetItem(ui->itemsview);
            parent->setText(0,nestedMap["title"].toString());
            parent->setIcon(0,QIcon(":folder"));
            parent->setCheckState(0,Qt::Checked);
            foreach(QVariant items, nestedMap["children"].toList()) {
                QVariantMap item = items.toMap();
                url.setUrl(item["uri"].toString(),QUrl::StrictMode);
                if(!item["title"].toString().isEmpty() && url.isValid()==true &&
                        (url.scheme()=="http" || url.scheme()=="https" || url.scheme()=="ftp"))
                {
                    QTreeWidgetItem *child=new QTreeWidgetItem(parent);
                    child->setText(0,item["title"].toString());
                    child->setCheckState(0,Qt::Checked);
                    child->setToolTip(0,item["uri"].toString());
                    child->setData(0,Qt::UserRole,item["uri"]);
                    child->setIcon(0,QIcon(":link"));
                    parent->addChild(child);
                }

            }
        }

    }
}

#include <QFileDialog>
void Import::on_pushButton_clicked()
{
    QString file_find;
    if(import_from=="firefox")
        file_find="profiles.ini(profiles.ini)";
    else if(import_from=="chromium")
        file_find="Bookmarks(Bookmarks)";///
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "",file_find );
    if(!fileName.isEmpty())
    {
        if(import_from=="firefox")
        {
            QSettings settings(fileName,QSettings::IniFormat);
            QFileInfo file(fileName);
            file.absoluteDir();
            int i=0;
            manual=true;
            ui->profillist->clear();
            manual=false;
            QString path;
            while(settings.value("Profile"+QString::number(i)+"/Path",NULL)!=NULL)
            {
                if(settings.value("Profile"+QString::number(i)+"/IsRelative",1)==1)
                {
                    path=file.absoluteDir().path();
                    path+=QDir::toNativeSeparators("/Mozilla/Firefox/")+settings.value("Profile"+QString::number(i)+"/Path").toString()+"/";
                }
                else
                {
                    path=settings.value("Profile"+QString::number(i)+"/Path").toString()+QDir::toNativeSeparators("/");
                }
                ui->profillist->addItem(settings.value("Profile"+QString::number(i++)+"/Name",NULL).toString(),path);
            }
        }
        else if(import_from=="chromium")
        {
            manual=true;
            ui->profillist->clear();
            manual=false;
            ui->profillist->addItem("Default",fileName);
        }

    }

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

        if(item->parent()->checkState(column)!=Qt::Checked && item->checkState(column)==Qt::Checked)
        {
            chiled=true;
            item->parent()->setCheckState(column,Qt::Checked);

        }

    }
    chiled=false;
}
#include<QTreeWidgetItemIterator>
void Import::renderPreview(int percent)
{
    ui->image->setValue(percent);
}
void Import::saveimage()
{

    if(QFile::exists(tmpdir+fname))
    {
        QPixmap resized;
        QPixmap origin(tmpdir+fname);
        if(origin.height()>=1600){
            origin = origin.copy(0,0,origin.width(),origin.width()/1.2);
        }
        resized = origin.scaled(origin.width()/1.5,origin.width()/1.9,Qt::KeepAspectRatio,Qt::FastTransformation );
        resized.save(tmpdir+fname);
        resized=QPixmap();
        origin=QPixmap();
    }
finished=true;
}


 #include <QTimer>
void Import::on_pushButton_2_clicked()
{
    int i=0;
    QTreeWidgetItemIterator it(ui->itemsview);
    while (*it) {//i++;
        ///if ((*it)->checkState(0)==Qt::Checked && (*it)->childCount()==0)
            i++;
        ++it;
    }
    qDebug()<<i;
    ui->itemsall->setMaximum(i);
    ui->itemsview->hide();
    ui->widget->hide();
    ui->pushButton_2->hide();
    this->open_bookmarks();
    connect(&websnap.m_page, SIGNAL(loadProgress(int)), this, SLOT(renderPreview(int)));
    connect(&websnap, SIGNAL(finished()), this, SLOT(saveimage()));
    this->manual=false;
    websnap.m_page.settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
    ui->abort->show();
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
            fname=QString(QCryptographicHash::hash((*items)->data(0,Qt::UserRole).toString().toLocal8Bit(),QCryptographicHash::Md5).toHex())+".png";
            websnap.load( guessUrlFromString( (*items)->data(0,Qt::UserRole).toString().toLatin1().data()), 100, tmpdir+fname,1024);
            while (finished!=true) { qApp->processEvents(QEventLoop::WaitForMoreEvents); }
            if(QFile::exists(tmpdir+fname))
            {
                QFile::copy(tmpdir+fname,imgdir+fname);
                QFile::setPermissions(imgdir+fname,QFile::ReadOwner | QFile::WriteOwner |
                                      QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                      QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);

                QDomElement  element=doc.createElement("bookmark");
                element.setAttribute("url",(*items)->data(0,Qt::UserRole).toString());
                QDomText elemlText =doc.createTextNode((*items)->text(0));
                element.setAttribute("image",fname);
                element.appendChild(elemlText);
                elem.appendChild(element);
            }
            this->save_bookmarks();
        }
        ++items;
    }
    this->save_bookmarks();
    QMessageBox::warning(0, QObject::tr("Info"), QObject::tr("We recommend to restart the application\n for better performance."));

    this->close();
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
    file.setFileName(QDir::toNativeSeparators ( QApplication::applicationDirPath()+QDir::toNativeSeparators("/") ) +"links.xml");
    file.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream out(&file);
    doc.save(out,0);
    file.close();

}

void Import::on_abort_clicked()
{
    websnap.m_page.action(websnap.m_page.Stop);
    websnap.m_fileName="blabla_not_found.png";
    websnap.m_page.mainFrame()->setHtml("<h1>not found</h1>");
    finished=true;
}
