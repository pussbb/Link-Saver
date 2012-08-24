#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDialog>
#include <webcapture.h>
#include <QWebFrame>
#include <QWebElement>
#include <engine.h>

namespace Ui {
class LinkDialog;
}

class LinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinkDialog(QWidget *parent = 0);
    ~LinkDialog();
    QVariantMap getData() const;
    void setElement(const QDomElement element);
private slots:
    void on_toolButton_clicked();
    void saveImave(bool);
private:
    WebCapture *capture;
    Ui::LinkDialog *ui;
    QString fileName;
};

#endif // LINKDIALOG_H
