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
        dir.mkdir(dialog->getDir() + QDir::toNativeSeparators("/images"));
        m_engine->create(dialog->getName(),dialog->getDir());
    }
    dialog->deleteLater();
}

