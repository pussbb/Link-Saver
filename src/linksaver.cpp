#include "linksaver.h"
#include "ui_linksaver.h"
#include "newlist.h"
#include "QToolButton"
#include "QInputDialog"
#include "QDesktopWidget"

LinkSaver::LinkSaver(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::LinkSaver)
{
    ui->setupUi(this);

    buildLangMenu("qlinksaver");
    langMenuToMenuBar("menuOptions");

    m_engine = new Engine(this, appDir + QDir::toNativeSeparators("/links/"));
    flow = new LinksFlow();

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

    ui->actionDeleteLink->setEnabled(false);
    ui->actionDeleteCategory->setEnabled(false);

    connect(ui->linksTree, SIGNAL(folderSelected()),
            this, SLOT(folderSelected()));
    connect(ui->linksTree, SIGNAL(linkSelected()),
            this, SLOT(linkSelected()));
    connect(ui->linksTree, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(treeCustomMenu(QPoint)));
    connect(ui->linksTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui->actionNewLinkList);
    trayIconMenu->addAction(ui->actionNewCategory);
    trayIconMenu->addAction(ui->actionNewLink);
    trayIconMenu->addAction(ui->actionExit);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/app.png"));
    trayIcon->show();
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;
    QDesktopWidget *desktop = QApplication::desktop();
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
}

LinkSaver::~LinkSaver()
{
    delete ui;
}

void LinkSaver::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:   show();     break;
    case QSystemTrayIcon::MiddleClick:
        trayIcon->showMessage(tr("Link Saver"),tr("Simple Program to Save Links"), QSystemTrayIcon::Information,
                              5 * 1000);
        break;
    default: ;
    }
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
    settings.setValue("general.lastopened", linksList->currentText());

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

void LinkSaver::on_actionNewCategory_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Category"),
                                         tr("Name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && ! text.isEmpty())
    {
        ui->linksTree->addFolder(text);
    }
}

void LinkSaver::on_actionDeleteList_triggered()
{
    QString dir = m_engine->documentDir(linksList->currentText());
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Delete list"));
    msgBox.setText(
                tr("Do you realy what to delete %1")
                .arg(linksList->currentText())
                );
    msgBox.setInformativeText(tr("It will be removed whole directory \n%1").arg(dir));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if (msgBox.exec() == QMessageBox::Yes) {
        if ( removeDir(dir)) {
            linksList->removeItem(linksList->currentIndex());
        }
        else {
            QMessageBox::warning(0,  QObject::tr("Deleting list"),
                                 QObject::tr("Could not delete folder and files.\n%1")
                                 .arg(dir));
        }
    }
}
bool LinkSaver::removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden
                                                    | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }

    return result;
}


void LinkSaver::on_actionDeleteCategory_triggered()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Delete category"));
    msgBox.setText(
                tr("Do you realy what to category \n %1")
                .arg(ui->linksTree->currentText())
                );
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if (msgBox.exec() == QMessageBox::Yes) {
        if ( ! ui->linksTree->removeSelectedItem() ) {
            QMessageBox::warning(0,  QObject::tr("Deleting category"),
                                 QObject::tr("Could not delete category.\n%1")
                                 .arg(ui->linksTree->currentText()));
        }
    }
}

void LinkSaver::folderSelected()
{
    ui->actionDeleteLink->setEnabled(false);
    ui->actionDeleteCategory->setEnabled(true);
}

void LinkSaver::linkSelected()
{
    ui->actionDeleteLink->setEnabled(true);
    ui->actionDeleteCategory->setEnabled(false);
}

void LinkSaver::treeCustomMenu(QPoint pos)
{
    QMenu *m = new QMenu();
    m->addAction(ui->actionNewLink);
    m->addAction(ui->actionNewCategory);
    switch(ui->linksTree->selectedItemType()) {
        case LinksTree::Folder :
            m->addAction(ui->actionEdit);
            m->addAction(ui->actionDeleteCategory);
            break;
        case LinksTree::Link :
            m->addAction(ui->actionEdit_Link);
            m->addAction(ui->actionDeleteLink);
            break;
        default:
            break;
    }

    m->exec(ui->linksTree->mapToGlobal(pos));
}

#include "linkdialog.h"
void LinkSaver::on_actionNewLink_triggered()
{
    LinkDialog *dialog = new LinkDialog(this);
    if(dialog->exec() == QDialog::Accepted)
    {
        ui->linksTree->addLink(dialog->getData());
    }
    dialog->deleteLater();
}

void LinkSaver::on_actionDeleteLink_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Delete link"));
    msgBox.setText(
                tr("Do you realy what to delete link \n %1")
                .arg(ui->linksTree->currentText())
                );
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if (msgBox.exec() == QMessageBox::Yes) {
        if ( ! ui->linksTree->removeSelectedItem() ) {
            QMessageBox::warning(0,  QObject::tr("Deleting link"),
                                 QObject::tr("Could not delete link.\n%1")
                                 .arg(ui->linksTree->currentText()));
        }
    }
}



void LinkSaver::itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if ( ui->linksTree->itemType(item) == LinksTree::Link)
    {
        QDomElement elem = ui->linksTree->itemDomElement(item);
        QDesktopServices::openUrl(QUrl(m_engine->nodeData(elem, Engine::Url), QUrl::TolerantMode));
    }
    else if (ui->linksTree->itemType(item) == LinksTree::Folder){
        flow->show(ui->linksTree->itemDomNode(item), m_engine->documentImagesPath());
    }
}

#include <settings.h>
void LinkSaver::on_actionSettings_triggered()
{
    Settings *dialog = new Settings(this);
    if(dialog->exec())
    {
        dialog->deleteLater();
    }
}

void LinkSaver::on_actionEdit_triggered()
{
    QDomElement elem = ui->linksTree->selectedDomItem();
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Category"),
                                         tr("Name:"), QLineEdit::Normal,
                                         Engine::nodeData(elem, Engine::Title), &ok);
    if (ok && ! text.isEmpty())
    {
        elem.setAttribute("name", text);
        m_engine->save();
        ui->linksTree->currentItem()->setText(0, text);
    }
}

void LinkSaver::on_actionEdit_Link_triggered()
{
    QDomElement elem = ui->linksTree->selectedDomItem();
    LinkDialog *dialog = new LinkDialog(this);
    dialog->setElement(elem, m_engine->documentDir()+QDir::toNativeSeparators("/images/"));
    if(dialog->exec() == QDialog::Accepted)
    {
        m_engine->updateLink(elem, dialog->getData());
        ///ui->linksTree->addLink(dialog->getData());
    }
    dialog->deleteLater();
}
