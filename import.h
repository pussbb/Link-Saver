#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>
#include "QDir"
#include <QMessageBox>
#include <QFile>
#include <QSettings>
#include "qt-json/json.h"
#include <qtextstream.h>
#include <QTreeWidgetItem>
#include <QProgressDialog>
#include <addurl.h>
#include <QDomDocument>
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
    void chromium_bookmaks();
    WebCapture websnap;
    QDir dir;
    QString fname;
    QDomDocument doc;
    QDomElement elem;
    QFile file;
    bool chiled;
    bool finished;
    bool manual;
    QString import_from;
    ~Import();

private slots:
    void on_profillist_currentIndexChanged(int index);
    void build_tree(QString file);
    void firefox_json(QVariantMap result);
    void chromium_json(QVariantMap result,QString section,QString name);
    void chromium_json(QVariant result,QString section,QString name);
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
