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
#include <QtGui>
#include <QtWebKit>
#include <QProgressDialog>
#include <addurl.h>
#include <QDomDocument>
#include <QFile>
#include <QDate>
#include <QXmlStreamWriter>
namespace Ui {
    class Import;
}

class Import : public QDialog
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = 0);
    void firefox_profiles();
    WebCapture websnap;
    QDir dir;
     QString fname;
    QDomDocument doc;
    QDomElement elem;
    QFile file;
    bool chiled;
    bool finished;
    QString import_from;
    ~Import();

private slots:
    void on_profillist_currentIndexChanged(int index);
    void build_tree(QString file);
    void on_pushButton_clicked();
    void on_itemsview_itemChanged(QTreeWidgetItem* item, int column);
    void renderPreview(int percent);
    void saveimage();
    void open_bookmarks();
    void save_bookmarks();
    void on_pushButton_2_clicked();

private:
    Ui::Import *ui;

};

#endif // IMPORT_H
