#ifndef NEWLIST_H
#define NEWLIST_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class NewList;
}

class NewList : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewList(QWidget *parent = 0);
    ~NewList();
    QString getName();
    QString getDir();
private slots:
    void on_selectDir_clicked();
    void accept();
private:
    Ui::NewList *ui;
};

#endif // NEWLIST_H
