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
private:
    Ui::Import *ui;

};

#endif // IMPORT_H
