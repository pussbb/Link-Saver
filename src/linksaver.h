#ifndef LINKSAVER_H
#define LINKSAVER_H

#include <qcorewindow.h>

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

private:
    Ui::LinkSaver *ui;
};

#endif // LINKSAVER_H
