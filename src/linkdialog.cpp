#include "linkdialog.h"
#include "ui_linkdialog.h"

LinkDialog::LinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkDialog)
{
    ui->setupUi(this);
}

LinkDialog::~LinkDialog()
{
    delete ui;
}
