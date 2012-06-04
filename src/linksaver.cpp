#include "linksaver.h"
#include "ui_linksaver.h"
#include "newlist.h"


LinkSaver::LinkSaver(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::LinkSaver)
{
    ui->setupUi(this);

    buildLangMenu("qlinksaver");
    langMenuToMenuBar("menuOptions");

    m_engine = new Engine(this, appDir + QDir::toNativeSeparators("/links/"));
    linksList = new  QComboBox();
    linksList->setEditable(false);
    initLinksList();
    ui->mainToolBar->addWidget(linksList);
}

LinkSaver::~LinkSaver()
{
    delete ui;
}

void LinkSaver::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void LinkSaver::on_actionExit_triggered()
{
    exit(0);
}

void LinkSaver::on_actionNewLinkList_triggered()
{
    NewList *dialog = new NewList(this);
    if(dialog->exec() == QDialog::Accepted)
    {
        QDir dir;
        QString imgDir = dialog->getDir() + QDir::toNativeSeparators("/images");
        bool ok = dir.mkdir(imgDir);
        if ( ! ok)
        {
            QMessageBox::warning(0,  QObject::tr("Warning"),
                                 QObject::tr("Error creating folder.\n%1")
                                 .arg(imgDir));
        }
        QDomDocument doc = m_engine->create(dialog->getName(),dialog->getDir());
        QString name = doc.documentElement().attribute("name");
        linksList->addItem(name);
    }
    dialog->deleteLater();
}

void LinkSaver::linkListChangedIndex(int index)
{

    if (index == -1)
        return;

}

void LinkSaver::initLinksList()
{

    QDirIterator directory_walker(appDir + "data", QStringList("links.xml"), QDir::Files | QDir::NoSymLinks
                                      |QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(directory_walker.hasNext()) {
            directory_walker.next();
            QDomDocument doc = m_engine->openDocument(directory_walker.filePath());
            QString name = doc.documentElement().attribute("name");
            linksList->addItem(name);
    }

    QString lastOpenedName = settings.value("general.lastopened", "").toString();

    connect(linksList, SIGNAL(currentIndexChanged(int)), this,SLOT(linkListChangedIndex(int)));

    int lastOpened = 0;
    if ( ! lastOpenedName.isEmpty() ) {
        lastOpened = linksList->findText(lastOpenedName);
    }

    // try to select first valid
    if ( lastOpened == -1)
        lastOpened = 0;

    linksList->setCurrentIndex(-1);
    linksList->setCurrentIndex(lastOpened);
}

