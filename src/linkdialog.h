#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDialog>

namespace Ui {
class LinkDialog;
}

class LinkDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LinkDialog(QWidget *parent = 0);
    ~LinkDialog();
    
private:
    Ui::LinkDialog *ui;
};

#endif // LINKDIALOG_H
