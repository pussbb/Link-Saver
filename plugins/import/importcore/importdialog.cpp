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

QTreeWidgetItem *ImportDialog::appendItem(const QString &name,
                                          const QString &url = "",
                                          bool isFolder = FALSE,
                                          QTreeWidgetItem *parent)
{

    QTreeWidgetItem *item;

    if (parent == NULL)
        item = new QTreeWidgetItem(ui.links);
    else
        item = new QTreeWidgetItem(parent);

    item->setText(0, name);
    if (isFolder) {
        item->setIcon(0, QIcon(":folder"));
    }
    else {
        item->setIcon(0, QIcon(":link"));
        item->setText(1, url);
    }

    item->setCheckState(0, Qt::Checked);
    return item;
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
