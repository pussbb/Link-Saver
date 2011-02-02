#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "QSettings"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    QSettings settings;
    ~Settings();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
