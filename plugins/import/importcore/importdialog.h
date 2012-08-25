#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "ui_importdialog.h"

class ImportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImportDialog(QWidget *parent = 0);
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::ImportDialog ui;
};

#endif // IMPORTDIALOG_H
