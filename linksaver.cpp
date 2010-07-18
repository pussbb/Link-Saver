#include "linksaver.h"
#include "ui_linksaver.h"
#include <QDebug>
#include <QDesktopWidget>
#define tmpdir QDir::toNativeSeparators ( QDir::tempPath()+"/" )
#define imgdir QDir::toNativeSeparators (QApplication::applicationDirPath()+"/images/" )
LinkSaver::LinkSaver(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::LinkSaver)
{
    ui->setupUi(this);
    ///

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
                    child->setText(0,elem.childNodes().item(w).toElement().text());
                    child->setData(0,32,w);//elem.childNodes().item(w).lineNumber() );
                    child->setData(0,33,"bookmark");
                    child->setIcon(0,QIcon(":/res/link.png"));
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
        //  QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
        trayIcon->showMessage("Link Saver","Simple Program to Save Links", QSystemTrayIcon::Information,
                              5 * 1000);
        break;
    default: ;
    }
}
void LinkSaver::closeEvent(QCloseEvent *event)
{
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
        QMenu m(tr("Cat menu"),this);
        m.addAction(ui->RemoveFolderItem);

        m.exec(ui->linkcat->mapToGlobal(pos));
    }
}

void LinkSaver::on_RemoveFolderItem_triggered()
{  if(ui->linkcat->currentItem()->data(0,33).toString()=="folder")
    {
        msgBox.setText(QString::fromUtf8("Are you sure want delete item."));
        msgBox.setInformativeText(QString::fromUtf8("All Link in this category will be deleted too"));
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
        msgBox.setText(QString::fromUtf8("Are you sure want delete Bookmark."));
        msgBox.setInformativeText(QString::fromUtf8("Link  will be deleted "));
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
            //elem.setTagName("bookmark");
            elem.setAttribute("url",text);
            QDomText elemlText =doc.createTextNode(QString(url->websnap.m_page.mainFrame()->evaluateJavaScript("document.title").toString()));
            //elemlText.toElement().setAttribute();
            elem.setAttribute("image",url->fname);
            elem.appendChild(elemlText);
            // elem.setNodeValue(QString(url->websnap.m_page.mainFrame()->evaluateJavaScript("document.title").toString()));
            //  qDebug()<<url->websnap.m_page.mainFrame()->evaluateJavaScript("document.title").toString();
            docElem.childNodes().item(url->get_cat().toInt()).toElement().appendChild(elem);
            save_to_file();
        }
       // while(url->isVisible()){qApp->processEvents(QEventLoop::WaitForMoreEvents );}
       delete url;
        //delete &url;
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
                w->addSlide(QImage(imgdir+elem.childNodes().item(i).toElement().attribute("image","not found")),
                            elem.childNodes().item(i).toElement().text(),elem.childNodes().item(i).toElement().attribute("url","not found"));
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
        item->data(0,32).toInt();
        QString urlgo=doc.documentElement().childNodes().item(item->parent()->data(0,32).toInt()).childNodes().item(item->data(0,32).toInt()).toElement().attribute("url","not found");
        //   qDebug()<<doc.childNodes().at(item->data(0,32).toInt()).toElement().text();
        QDesktopServices::openUrl(QUrl(urlgo, QUrl::TolerantMode));
    }
}
#include "about.h"
void LinkSaver::on_actionAbout_triggered()
{
About *about=new About(this);
about->exec();
}
