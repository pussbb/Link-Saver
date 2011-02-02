#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    if(settings.value("hideonstart",false)==true) ui->hideonstartup->setChecked(true);
    if(settings.value("langtodef",false)==true) ui->langtodef->setChecked(true);
    if(settings.value("toicontray",false)==true) ui->toicontray->setChecked(true);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_buttonBox_accepted()
{
    if(ui->hideonstartup->isChecked())    settings.setValue("hideonstart",true);
    else settings.setValue("hideonstart",false);
    if(ui->langtodef->isChecked())    settings.setValue("langtodef",true);
    else settings.setValue("langtodef",false);
    if(ui->toicontray->isChecked())    settings.setValue("toicontray",true);
    else settings.setValue("toicontray",false);
}
