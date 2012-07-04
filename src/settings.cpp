#include "settings.h"
#include "ui_settings.h"
#include <QSettings>
Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    QSettings settings;
    ui->saveChoosenLang->setChecked(settings.value("Core/save_locale", true).toBool());
    ui->hideOnStart->setChecked(settings.value("App/hideOnStart", false).toBool());
    ui->screenshortInToolTip->setChecked(settings.value("App/screenshortInToolTip", false).toBool());
    ui->linksMenuInTray->setChecked(settings.value("App/linksMenuInTray", false).toBool());
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_buttonBox_accepted()
{
    QSettings settings;
    settings.setValue("Core/save_locale", ui->saveChoosenLang->isChecked());
    settings.setValue("App/hideOnStart", ui->hideOnStart->isChecked());
    settings.setValue("App/screenshortInToolTip", ui->screenshortInToolTip->isChecked());
    settings.setValue("App/linksMenuInTray", ui->linksMenuInTray->isChecked());
}
