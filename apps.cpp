#include "apps.h"
#include "ui_apps.h"
#include <QFileDialog>
#include <QMessageBox>


Apps::Apps(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Apps)
{
    ui->setupUi(this);
    this->valid=false;
}

Apps::~Apps()
{
    delete ui;
}

void Apps::on_toolButton_clicked()
{
    ui->exepath->setText(QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Executable(*.*)")));
}

void Apps::on_toolButton_2_clicked()
{
    ui->appicon->setText(QFileDialog::getOpenFileName(this,
                                                      tr("Open Image"), "", tr("Image Files (*.png *.jpg *.svg)")));
}

void Apps::on_toolButton_3_clicked()
{
    ui->screenshot->setText(QFileDialog::getOpenFileName(this,
                                                         tr("Open Image"), "", tr("Image Files (*.png *.jpg *.svg)")));
}
void Apps::additem(QString name, int index)
{
    ui->comboBox->addItem(name,index);
}
QString Apps::getitem(int index)
{
    switch(index)
    {
    case 0:            return ui->appname->text();break;
    case 1:            return ui->appicon->text();break;
    case 2:             return ui->exepath->text();break;
    case 3:             return ui->screenshot->text();break;
    case 4:             return ui->comboBox->itemData(ui->comboBox->currentIndex(),32).toString();;break;
    default: break;
    }
}

void Apps::on_buttonBox_clicked(QAbstractButton* button)
{
    if(ui->buttonBox->buttonRole(button)==0 ){//ui->appicon->text().isEmpty()!=true
        if( !ui->appname->text().isEmpty()
            || !ui->exepath->text().isEmpty() || !ui->screenshot->text().isEmpty())
        {
            this->valid=true;this->accept();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Please fill al filieds.");
            msgBox.exec();

        }
    }
    else
    {
        this->close();
    }
}
