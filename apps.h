#ifndef APPS_H
#define APPS_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
    class Apps;
}

class Apps : public QDialog
{
    Q_OBJECT

public:
    explicit Apps(QWidget *parent = 0);
    bool valid;
    void additem(QString name, int index,bool current = false);
    QString getitem(int index);
    void setData(int index,QString str);
    ~Apps();

private:
    Ui::Apps *ui;

private slots:
    void on_buttonBox_clicked(QAbstractButton* button);
    void on_toolButton_3_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_clicked();
};

#endif // APPS_H
