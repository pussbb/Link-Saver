#include "importdialog.h"
#include <QDebug>

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    bool ok = QMetaObject::invokeMethod(parent, "getEngine", Qt::DirectConnection,
                                      Q_RETURN_ARG(Engine *, m_engine));
    qDebug()<<ok<<m_engine->documentImagesPath();
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
