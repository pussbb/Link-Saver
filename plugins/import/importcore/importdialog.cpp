#include "importdialog.h"

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
}

void ImportDialog::clearData()
{
    ui.links->clear();
}

void ImportDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}
