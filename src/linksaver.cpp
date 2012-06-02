#include "linksaver.h"
#include "ui_linksaver.h"

LinkSaver::LinkSaver(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::LinkSaver)
{
    ui->setupUi(this);

    buildLangMenu("qlinksaver");
    langMenuToMenuBar("menuOptions");

}

LinkSaver::~LinkSaver()
{
    delete ui;
}

void LinkSaver::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}
