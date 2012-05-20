#include "linksaver.h"
#include "ui_linksaver.h"

LinkSaver::LinkSaver(QWidget *parent) :
    QCoreWindow(parent),
    ui(new Ui::LinkSaver)
{
    ui->setupUi(this);
}

LinkSaver::~LinkSaver()
{
    delete ui;
}
