#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>
#include "QDir"
#include <QMessageBox>
#include <QFile>
#include <QSettings>
#include "qt-json/json.h"
#include <qfile.h>
#include <qtextstream.h>
#include <QTreeWidgetItem>
namespace Ui {
    class Import;
}

class Import : public QDialog
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = 0);
    void firefox_profiles();
     QDir dir;
    QString import_from;
    ~Import();

private slots:
    void on_profillist_currentIndexChanged(int index);
    void build_tree(QString file);
    void on_pushButton_clicked();

    void on_itemsview_itemChanged(QTreeWidgetItem* item, int column);

private:
    Ui::Import *ui;

};

#endif // IMPORT_H
