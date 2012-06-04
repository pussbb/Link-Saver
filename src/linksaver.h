#ifndef LINKSAVER_H
#define LINKSAVER_H

#include <qcorewindow.h>
#include <engine.h>
#include <QComboBox>

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
private:
    Ui::LinkSaver *ui;
    Engine *m_engine;
    QComboBox *linksList;
    QSettings m_settings;
    void initLinksList();
};

#endif // LINKSAVER_H
