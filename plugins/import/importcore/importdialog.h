#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "ui_importdialog.h"
#include <engine.h>
#include<QTreeWidgetItemIterator>
#include <QTime>
#include <QTimer>

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = 0);
    void clearData();
    inline QComboBox * getProfileList() const
    { return ui.profilesList;}
    QTreeWidgetItem * appendItem(const QString &name, const QString &url, bool isFolder, QTreeWidgetItem *parent = NULL);

protected:
    void changeEvent(QEvent *e);
private slots:
    void on_pushButton_clicked();
    void updateDisplay();
    void renderPreview(int percent);

private:
    Ui::ImportDialog ui;
    Engine *m_engine;
    QTime time;
    QTime itemTime;
    QTimer timer;
};

#endif // IMPORTDIALOG_H
