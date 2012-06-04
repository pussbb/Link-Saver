#include "linksaver.h"
#include "ui_linksaver.h"
#include "newlist.h"
#include "QToolButton"

LinkSaver::LinkSaver(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::LinkSaver)
{
    ui->setupUi(this);

    buildLangMenu("qlinksaver");
    langMenuToMenuBar("menuOptions");

    m_engine = new Engine(this, appDir + QDir::toNativeSeparators("/links/"));

    ui->linksTree->setEngine(m_engine);

    linksList = new  QComboBox();
    linksList->setEditable(false);

    ui->actionNewCategory->setEnabled(false);
    ui->actionNewLink->setEnabled(false);
    initLinksList();

    QToolButton *newButton = new QToolButton();
    newButton->setPopupMode(QToolButton::InstantPopup);
    newButton->setIcon(QIcon(":/tool/add.png"));
    newButton->addAction(ui->actionNewLinkList);
    newButton->addAction(ui->actionNewCategory);
    newButton->addAction(ui->actionNewLink);

    QToolButton *removeButton = new QToolButton();
    removeButton->setPopupMode(QToolButton::InstantPopup);
    removeButton->setIcon(QIcon(":/tool/delete.png"));
    removeButton->addAction(ui->actionDeleteList);
    removeButton->addAction(ui->actionDeleteCategory);
    removeButton->addAction(ui->actionDeleteLink);

    ui->mainToolBar->addWidget(newButton);
    ui->mainToolBar->addWidget(removeButton);
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

    ui->actionNewCategory->setEnabled(true);
    ui->actionNewLink->setEnabled(true);
    ui->linksTree->buildTree(linksList->currentText());
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

