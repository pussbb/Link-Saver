#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDialog>
#include <webcapture.h>
#include <QWebFrame>
#include <QWebElement>

namespace Ui {
class LinkDialog;
}

class LinkDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LinkDialog(QWidget *parent = 0);
    ~LinkDialog();
    
private slots:
    void on_toolButton_clicked();
    void saveImave(bool);
private:
    WebCapture *capture;
    Ui::LinkDialog *ui;
    QString fileName;
};

#endif // LINKDIALOG_H
