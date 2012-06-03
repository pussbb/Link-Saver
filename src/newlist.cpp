#include "newlist.h"
#include "ui_newlist.h"
#include <QFileDialog>
#include <QMessageBox>


NewList::NewList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewList)
{
    ui->setupUi(this);
}

NewList::~NewList()
{
    delete ui;
}

QString NewList::getName()
{
    return ui->name->text();
}

QString NewList::getDir()
{
    return ui->folder->text();
}

void NewList::on_selectDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
                                                        "",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        if(!dir.isEmpty())
        {
            QFileInfo d(dir);
            if(d.isWritable())
                ui->folder->setText(dir);
            else
            {
                QMessageBox::warning(0,  QObject::tr("Directory write protected"),
                                     QObject::tr("%1\nPlease choose another directory.")
                                     .arg(dir));
            }
        }
}

#include <QDebug>
void NewList::accept()
{
    QFileInfo d(ui->folder->text());
    if ( ! d.isDir()){

        QMessageBox::warning(0,  QObject::tr("Directory not found"),
                             QObject::tr("%1\nPlease choose another directory.")
                             .arg(ui->folder->text()));
        return;
    }
    if ( ! d.isWritable()) {

        QMessageBox::warning(0,  QObject::tr("Directory write protected"),
                             QObject::tr("%1\nPlease choose another directory.")
                             .arg(ui->folder->text()));
        return;
    }

    QFileInfo f(d.absoluteFilePath() + QDir::toNativeSeparators("/links.xml"));
    qDebug()<<f.absoluteFilePath();
    if ( f.exists()) {

        QMessageBox::warning(0,  QObject::tr("Directory already contains link list"),
                             QObject::tr("Please choose another directory."));
        return;
    }

    if (  ui->name->text().isEmpty()) {

        QMessageBox::warning(0,  QObject::tr("Name is empty"),
                             QObject::tr("Please type your name of list."));
        return;
    }

    QDialog::accept();
}
