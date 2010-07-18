#include "about.h"
#include "ui_about.h"
#include "QFile"
#include "QTextStream"
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QFile file(":/LICENSE.LGPL");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       // qDebug()<<"canot open the file";
    }
    QTextStream in(&file);
   ///QString string= ;
   ui->textBrowser->setText(in.readAll());
}

About::~About()
{
    delete ui;
}
///file:///media/OldHome/pussbb/qt_projets/HelpWorld/HW/3thd/LICENSE.LGPL
void About::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
