#ifndef LINKSAVER_H
#define LINKSAVER_H

#include <QMainWindow>
#include "QSystemTrayIcon"
#include <QMenu>
#include <QInputDialog>
#include <QDomDocument>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QTextStream>
#include <QTreeWidgetItem>
namespace Ui {
    class LinkSaver;
}

class LinkSaver : public QMainWindow {
    Q_OBJECT
public:
    explicit LinkSaver(QWidget *parent = 0);
    ~LinkSaver();
    QSystemTrayIcon *trayIcon;
     QMenu *trayIconMenu;
     QDomDocument doc;
     QFile file;
     QMessageBox msgBox;
protected:
    void changeEvent(QEvent *e);
void closeEvent(QCloseEvent *event);
private:
    Ui::LinkSaver *ui;

private slots:
void on_actionAdd_App_triggered();
void on_actionAbout_triggered();
void on_linkcat_itemDoubleClicked(QTreeWidgetItem* item, int column);
void on_actionADD_triggered();
void save_to_file();
void on_RemoveFolderItem_triggered();
void on_linkcat_customContextMenuRequested(QPoint pos);
void init_links();
void init_items();
void on_actionAdd_Category_triggered();
void on_actionAbout_QT_triggered();
void on_actionExit_triggered();
void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // LINKSAVER_H
