#ifndef LINKSAVER_H
#define LINKSAVER_H

#include <qcorewindow.h>
#include <engine.h>
#include <QComboBox>
#include <QTreeWidgetItem>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <linksflow.h>

namespace Ui {
  class LinkSaver;
}

class LinkSaver : public QCoreWindow
{
    Q_OBJECT

public:
    explicit LinkSaver(QWidget *parent = 0);
    ~LinkSaver();

private slots:
    void on_actionAbout_Qt_triggered();
    void on_actionExit_triggered();
    void on_actionNewLinkList_triggered();
    void linkListChangedIndex(int index);
    void on_actionNewCategory_triggered();

    void on_actionDeleteList_triggered();
    bool removeDir(const QString &dirName);

    void on_actionDeleteCategory_triggered();
    void folderSelected();
    void linkSelected();
    void treeCustomMenu(QPoint pos);
    void on_actionNewLink_triggered();

    void on_actionDeleteLink_triggered();
    void itemDoubleClicked(QTreeWidgetItem* item,int column);

    void on_actionSettings_triggered();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_actionEdit_triggered();

    void on_actionEdit_Link_triggered();

private:
    Ui::LinkSaver *ui;
    Engine *m_engine;
    QComboBox *linksList;
    QSettings m_settings;
    void initLinksList();
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    LinksFlow *flow;
};

#endif // LINKSAVER_H
