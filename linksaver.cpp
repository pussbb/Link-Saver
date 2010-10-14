#include "linksaver.h"
#include "ui_linksaver.h"
#include "apps.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QProcess>

#define tmpdir QDir::toNativeSeparators ( QDir::tempPath()+"/" )
#define imgdir QDir::toNativeSeparators (QApplication::applicationDirPath()+"/images/" )
#define appimgdir QDir::toNativeSeparators (QApplication::applicationDirPath()+"/apps/images/" )
#define appicondir QDir::toNativeSeparators (QApplication::applicationDirPath()+"/apps/icons/" )
LinkSaver::LinkSaver(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::LinkSaver)
{
    ui->setupUi(this);
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;
    screenWidth = desktop->width(); // get width of screen
    screenHeight = desktop->height(); // get height of screen
    windowSize = size(); // size of our application window
    width = windowSize.width();
    height = windowSize.height();
    // little computations
     x = screenWidth - width;
    y = screenHeight - height;
    y -= 50;
    // move window to desired coordinates
    move ( x, y );
    ///
    //check if dir exists
    QDir dir;
    dir.setPath(imgdir);
    if(!dir.exists())
    {
        if(!dir.mkdir(imgdir))
        {
            msgBox.setText(tr("Error creating directory:<br />")+imgdir);
        }
        else
        {
            QFile::setPermissions(imgdir,QFile::ReadOwner | QFile::WriteOwner |
                                  QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                  QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);
        }
    }
    dir.setPath(QDir::toNativeSeparators (QApplication::applicationDirPath()+"/apps/" ));
    if(!dir.exists())
    {
        if(!dir.mkdir(QDir::toNativeSeparators (QApplication::applicationDirPath()+"/apps/" )))
        {
            msgBox.setText(tr("Error creating directory:<br />")+QDir::toNativeSeparators (QApplication::applicationDirPath()+"/apps/" ));
        }
        else
        {
            QFile::setPermissions(QDir::toNativeSeparators (QApplication::applicationDirPath()+"/apps/" ),QFile::ReadOwner | QFile::WriteOwner |
                                  QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                  QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);
        }
    }
    dir.setPath(appimgdir);
    if(!dir.exists())
    {
        if(!dir.mkdir(appimgdir))
        {
            msgBox.setText(tr("Error creating directory:<br />")+appimgdir);
        }
        else
        {
            QFile::setPermissions(appimgdir,QFile::ReadOwner | QFile::WriteOwner |
                                  QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                  QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);
        }
    }
    dir.setPath(appicondir);
    if(!dir.exists())
    {
        if(!dir.mkdir(appicondir))
        {
            msgBox.setText(tr("Error creating directory:<br />")+appicondir);
        }
        else
        {
            QFile::setPermissions(appicondir,QFile::ReadOwner | QFile::WriteOwner |
                                  QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                  QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);
        }
    }
    //end of check if dir exists
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui->actionADD);
    trayIconMenu->addAction(ui->actionExit);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/res/2globe_128.png"));
    trayIcon->show();
    trayIcon->setContextMenu(trayIconMenu);

    ///
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    init_links();
}

void LinkSaver::init_links()
{ ///  QDir::toNativeSeparators ( QApplication::applicationDirPath()+"" )
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
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    doc.setContent(&file);
    file.close();
    init_items();
}
void LinkSaver::init_items()
{
    ui->linkcat->clear();
    // qDebug()<<doc.toString();
    QDomElement docElem = doc.documentElement();
    for(int i=0;i<docElem.childNodes().count();i++)
    {
        if(docElem.childNodes().item(i).toElement().tagName()=="folder") {
            QTreeWidgetItem *item=new QTreeWidgetItem(ui->linkcat);
            item->setText(0,docElem.childNodes().item(i).toElement().attribute("name"));
            item->setData(0,32,i);
            item->setData(0,33,"folder");
            item->setIcon(0,QIcon(":/res/Blank-Map-64.png"));
            ui->linkcat->addTopLevelItem(item);
            // ui->linkcat->addItem(docElem.childNodes().item(i).toElement().attribute("name"));
            QDomElement elem = docElem.childNodes().item(i).toElement();
            if(elem.hasChildNodes())
            {
                for(int w=0;w<elem.childNodes().count();w++)
                {
                    QTreeWidgetItem *child=new QTreeWidgetItem(item);
                    QDomAttr e=elem.childNodes().item(w).toElement().attributeNode("url");

                    if(e.value()=="app")
                    {
                        e=elem.childNodes().item(w).toElement().attributeNode("app");
                        child->setText(0,e.value());
                        e=elem.childNodes().item(w).toElement().attributeNode("icon");

                        if(e.value().isEmpty()!=true && QFile::exists(appicondir+e.value())){
                            child->setIcon(0,QIcon(appicondir+e.value()));
                            //child->setData(0,34,appicondir+e.value());
                        }
                        else
                        {
                            child->setIcon(0,QIcon(":appexec"));
                            // child->setData(0,34,":appexec");
                        }
                        child->setData(0,33,"app");
                    }
                    else{
                        child->setText(0,elem.childNodes().item(w).toElement().text());
                        child->setIcon(0,QIcon(":/res/link.png"));
                        child->setData(0,33,"bookmark");
                    }
                    child->setData(0,32,w);//elem.childNodes().item(w).lineNumber() );


                    item->addChild(child);
                }
            }
        }
    }
}

void LinkSaver::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:   show();     break;
    case QSystemTrayIcon::MiddleClick:
           trayIcon->showMessage("Link Saver","Simple Program to Save Links", QSystemTrayIcon::Information,
                              5 * 1000);
        break;
    default: ;
    }
}
void LinkSaver::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    if (trayIcon->isVisible()) {
        trayIcon->showMessage("Link Saver", tr("The program will keep running\n in the system tray. To terminate the program, \n choose Quit in the context menu  \n of the system tray entry."),
                              QSystemTrayIcon::Information, 5 * 1000);
        hide();

    }
}

LinkSaver::~LinkSaver()
{
    delete ui;
}

void LinkSaver::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void LinkSaver::on_actionExit_triggered()
{
    exit(0);
}

void LinkSaver::on_actionAbout_QT_triggered()
{
    QApplication::aboutQt();
}
void LinkSaver::save_to_file()
{
    file.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream out(&file);
    doc.save(out,0);
    file.close();
    //delete &out;
    init_items();
}

void LinkSaver::on_actionAdd_Category_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Category"),
                                         tr("Name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        QDomElement elem=doc.createElement("folder");
        elem.setAttribute("name",text);
        doc.documentElement().appendChild(elem);
        save_to_file();
    }
}

void LinkSaver::on_linkcat_customContextMenuRequested(QPoint pos)
{if(ui->linkcat->currentItem()->isSelected()){
        QMenu *m=new QMenu();
        pos.setX(pos.x()-5);
        pos.setY(pos.y()+25);
        m->addAction(ui->RemoveFolderItem);
        m->addAction(ui->actionEdit);
        m->exec(ui->linkcat->mapToGlobal(pos));
    }
}

void LinkSaver::on_RemoveFolderItem_triggered()
{  if(ui->linkcat->currentItem()->data(0,33).toString()=="folder")
    {
        msgBox.setText(tr("Are you sure want delete item."));
        msgBox.setInformativeText(tr("All Link in this category will be deleted too"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if(msgBox.exec()==QMessageBox::Yes) {
            doc.documentElement().removeChild(doc.documentElement().childNodes().item(ui->linkcat->currentItem()->data(0,32).toInt()));
            file.open(QIODevice::WriteOnly| QIODevice::Text);
            save_to_file();
        }
    }
    else
    {
        msgBox.setText(tr("Are you sure want delete Bookmark."));
        msgBox.setInformativeText(tr("Link  will be deleted "));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        if(msgBox.exec()==QMessageBox::Yes) {
            QDomNode node= doc.documentElement().childNodes().item(ui->linkcat->currentItem()->parent()->data(0,32).toInt());
            node.removeChild(node.childNodes().item(ui->linkcat->currentItem()->data(0,32).toInt()));
            QFile::remove(imgdir+node.childNodes().item(ui->linkcat->currentItem()->data(0,32).toInt()).toElement().attribute("image"));
            file.open(QIODevice::WriteOnly| QIODevice::Text);
            save_to_file();
        }
    }
}
#include "addurl.h"
void LinkSaver::on_actionADD_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Url"),
                                         tr("URL:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
        AddUrl* url=new AddUrl(this) ;
        url->load(text);
        QDomElement docElem = doc.documentElement();
        for(int i=0;i<docElem.childNodes().count();i++)
        {
            if(docElem.childNodes().item(i).toElement().tagName()=="folder") {
                url->additem(docElem.childNodes().item(i).toElement().attribute("name"),i);
            }
        }
        while(url->p->isVisible()){qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents);}
        if(url->exec()==QDialog::Accepted)
        {
            QFile::copy(tmpdir+url->fname,imgdir+url->fname);
            QFile::setPermissions(imgdir+url->fname,QFile::ReadOwner | QFile::WriteOwner |
                                  QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                  QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);
            QDomElement elem=doc.createElement("bookmark");
            elem.setAttribute("url",url->url);
            QDomText elemlText =doc.createTextNode(QString(url->title));
            //elemlText.toElement().setAttribute();
            elem.setAttribute("image",url->fname);
            elem.appendChild(elemlText);
            docElem.childNodes().item(url->get_cat().toInt()).toElement().appendChild(elem);
            save_to_file();
        }
       delete url;
    }
}
#include <pictureflow.h>
class Browser: public PictureFlow
{
public:
    Browser(): PictureFlow()
    {
        setWindowTitle("PictureFlow");
    }

    void keyPressEvent(QKeyEvent* event)
    {
        if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_Enter ||
           event->key() == Qt::Key_Return)
        {
            event->accept();
            close();
        }

        // checking the speed of rendering


        // for debugging only: Alt+F11 cycles the reflection effect
        if(event->key() == Qt::Key_F11)
            if(event->modifiers() == Qt::AltModifier)
            {
            qDebug("changing reflection effect...");
            switch(reflectionEffect())
            {
                //case NoReflection:      setReflectionEffect(PlainReflection); break;
            case PlainReflection:   setReflectionEffect(BlurredReflection); break;
            case BlurredReflection: setReflectionEffect(PlainReflection); break;
            default:                setReflectionEffect(PlainReflection); break;
            }
            event->accept();
            return;
        }

        PictureFlow::keyPressEvent(event);
    }
};

void LinkSaver::on_linkcat_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if(item->data(column,33).toString()=="folder")
    {
        if(item->childCount()>0){
            Browser* w = new Browser;
            w->setSlideSize(QSize(7*40, 5*40));
            w->resize(850, 270);
            QDomElement elem=doc.documentElement().childNodes().item(item->data(0,32).toInt()).toElement();
            for(int i=0;i<elem.childNodes().count();i++)
            {
                QString tag=elem.childNodes().item(i).toElement().attribute("url","not found");
                if(tag=="app")
                {
                    w->addSlide(QImage(appimgdir+elem.childNodes().item(i).toElement().attribute("image","not found")),
                                elem.childNodes().item(i).toElement().attribute("app","not found"),elem.childNodes().item(i).toElement().text(),"app");
                }
                else
                {
                    w->addSlide(QImage(imgdir+elem.childNodes().item(i).toElement().attribute("image","not found")),
                                elem.childNodes().item(i).toElement().text(),elem.childNodes().item(i).toElement().attribute("url","not found"),"");
                }
                 }

            w->setCenterIndex(w->slideCount()/2);
            w->setReflectionEffect(PictureFlow::PlainReflection);
            w->setBackgroundColor(Qt::gray);
            w->showFullScreen();
             while(w->isVisible()){qApp->processEvents(QEventLoop::WaitForMoreEvents );}
            delete w;
        }
    }
    else
    {
        //item->data(0,32).toInt();
        QString urlgo=doc.documentElement().childNodes().item(item->parent()->data(0,32).toInt()).childNodes().item(item->data(0,32).toInt()).toElement().attribute("url","not found");

        if(urlgo=="app")
        {
            QProcess *app= new QProcess();
            app->start(doc.documentElement().childNodes().item(item->parent()->data(0,32).toInt()).childNodes().item(item->data(0,32).toInt()).toElement().text());
       }
        else{
        QDesktopServices::openUrl(QUrl(urlgo, QUrl::TolerantMode));
           }
    }
}
#include "about.h"
void LinkSaver::on_actionAbout_triggered()
{
About *about=new About(this);
about->exec();
}
#include <QFileInfo>
void LinkSaver::on_actionAdd_App_triggered()
{
    Apps *app= new Apps(this);
    QDomElement docElem = doc.documentElement();
    for(int i=0;i<docElem.childNodes().count();i++)
    {
        if(docElem.childNodes().item(i).toElement().tagName()=="folder") {
            app->additem(docElem.childNodes().item(i).toElement().attribute("name"),i);
        }
    }
    if(app->exec()==QDialog::Accepted)
    {
        QDomElement elem=doc.createElement("bookmark");
        elem.setAttribute("url","app");
        elem.setAttribute("app",app->getitem(0));
        QDomText elemlText =doc.createTextNode(QString(app->getitem(2)));
        QFileInfo fi(app->getitem(3));
        QString img=fi.fileName();
        QFile::copy(app->getitem(3),appimgdir+img);
        elem.setAttribute("image",img);
        fi.setFile(app->getitem(1));
        QString icon=fi.fileName();
        QFile::copy(app->getitem(1),appicondir+icon);
        elem.setAttribute("icon",icon);
        elem.appendChild(elemlText);
        docElem.childNodes().item(app->getitem(4).toInt()).toElement().appendChild(elem);
        save_to_file();
    }
    delete app;
}

void LinkSaver::on_actionEdit_triggered()
{   //ui->linkcat->currentItem()->data(0,33).toString();
    QTreeWidgetItem *item=ui->linkcat->currentItem();
    QDomNode node;
    QDomElement elem;
    if(ui->linkcat->currentItem()->data(0,33).toString()=="folder")
    {
        bool ok;
        node= doc.documentElement().childNodes().item(item->data(0,32).toInt());
        QString text = QInputDialog::getText(this, tr("Add Category"),
                                             tr("Name:"), QLineEdit::Normal,
                                             node.toElement().attribute("name",""), &ok);
        if (ok && !text.isEmpty())
        {
            node.toElement().setAttribute("name",text);
            //QDomElement elem=doc.createElement("folder");
            //elem.setAttribute("name",text);
            //doc.documentElement().appendChild(elem);
            save_to_file();
            return;
        }
    }
    else
    {
        node= doc.documentElement().childNodes().item(item->parent()->data(0,32).toInt());
        elem=node.childNodes().item(item->data(0,32).toInt()).toElement();
    }
    if(ui->linkcat->currentItem()->data(0,33).toString()=="app")
    {
        Apps *app= new Apps(this);
        QDomElement docElem = doc.documentElement();
        for(int i=0;i<docElem.childNodes().count();i++)
        {
            if(docElem.childNodes().item(i).toElement().tagName()=="folder") {
                bool current=false;
                if(item->parent()->data(0,32).toInt()==i)
                {
                                current=true;
                }
                app->additem(docElem.childNodes().item(i).toElement().attribute("name"),i,current);
            }
        }


        app->setData(2,elem.text());
        app->setData(1,elem.attribute("icon",":appexec"));
        app->setData(0,elem.attribute("app",""));
        app->setData(3,elem.attribute("image","no image"));
        if(app->exec()==QDialog::Accepted)
        {
            QDomElement elem=doc.createElement("bookmark");
            elem.setAttribute("url","app");
            elem.setAttribute("app",app->getitem(0));
            QDomText elemlText =doc.createTextNode(QString(app->getitem(2)));
            QFileInfo fi(app->getitem(3));
            QString img=fi.fileName();
            QFile::copy(app->getitem(3),appimgdir+img);
            elem.setAttribute("image",img);
            fi.setFile(app->getitem(1));
            QString icon=fi.fileName();
            QFile::copy(app->getitem(1),appicondir+icon);
            elem.setAttribute("icon",icon);
            elem.appendChild(elemlText);
            docElem.childNodes().item(app->getitem(4).toInt()).toElement().appendChild(elem);
            node.removeChild(node.childNodes().item(item->data(0,32).toInt()));
            save_to_file();
        }
        delete app;
    }
    if(ui->linkcat->currentItem()->data(0,33).toString()=="bookmark")
    {
        AddUrl* url=new AddUrl(this) ;
        //url->load(text);
        QDomElement docElem = doc.documentElement();
        for(int i=0;i<docElem.childNodes().count();i++)
        {
            if(docElem.childNodes().item(i).toElement().tagName()=="folder") {
                bool current=false;
                if(item->parent()->data(0,32).toInt()==i)
                {
                                current=true;
                }
                url->additem(docElem.childNodes().item(i).toElement().attribute("name"),i,current);
            }
        }
        url->set_Data(item->text(0),2);
        QString urls=doc.documentElement().childNodes().item(item->parent()->data(0,32).toInt()).childNodes().item(item->data(0,32).toInt()).toElement().attribute("url","not found");
        url->set_Data(urls,1);
        url->set_Data(imgdir+elem.attribute("image",""),3);
        url->set_Data(elem.attribute("image",""),4);
        if(url->exec()==QDialog::Accepted)
        {
            if(url->changed)
            {
                QFile::remove(imgdir+elem.attribute("image",""));
                QFile::copy(tmpdir+url->fname,imgdir+url->fname);
                QFile::setPermissions(imgdir+url->fname,QFile::ReadOwner | QFile::WriteOwner |
                                      QFile::ExeOwner |  QFile::ReadUser | QFile::WriteUser | QFile::ExeUser | QFile::ReadGroup |
                                      QFile::WriteGroup | QFile::ExeGroup | QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);
            }

            QDomElement elem=doc.createElement("bookmark");
            elem.setAttribute("url",url->url);
            QDomText elemlText =doc.createTextNode(QString(url->title));
            //elemlText.toElement().setAttribute();
            elem.setAttribute("image",url->fname);
            elem.appendChild(elemlText);
            docElem.childNodes().item(url->get_cat().toInt()).toElement().appendChild(elem);
            node.removeChild(node.childNodes().item(item->data(0,32).toInt()));
            save_to_file();
        }

    }

}
