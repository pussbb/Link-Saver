#include "importdialog.h"
#include <QDebug>

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    bool ok = QMetaObject::invokeMethod(parent, "getEngine", Qt::DirectConnection,
                                      Q_RETURN_ARG(Engine *, m_engine));
    qDebug()<<ok<<m_engine->documentImagesPath();
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
}

void ImportDialog::clearData()
{
    ui.links->clear();
}

QTreeWidgetItem *ImportDialog::appendItem(const QString &name,
                                          const QString &url = "",
                                          bool isFolder = FALSE,
                                          QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item;

    if (parent == NULL)
        item = new QTreeWidgetItem(ui.links);
    else
        item = new QTreeWidgetItem(parent);

    item->setText(0, name);
    if (isFolder) {
        item->setIcon(0, QIcon(":folder"));
    }
    else {
        item->setIcon(0, QIcon(":link"));
        item->setText(1, url);
    }

    item->setCheckState(0, Qt::Checked);
    return item;
}

void ImportDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

void ImportDialog::updateDisplay()
{
    int secs = time.elapsed() / 1000;
    int mins = (secs / 60) % 60;
    int hours = (secs / 3600);
    secs = secs % 60;
    ui.totalTime->setText(QString("%1:%2:%3")
                            .arg(hours, 2, 10, QLatin1Char('0'))
                            .arg(mins, 2, 10, QLatin1Char('0'))
                            .arg(secs, 2, 10, QLatin1Char('0')) );
    secs = itemTime.elapsed() / 1000;
    mins = (secs / 60) % 60;
    hours = (secs / 3600);
    secs = secs % 60;
    ui.time->setText(QString("%1:%2:%3")
                      .arg(hours, 2, 10, QLatin1Char('0'))
                      .arg(mins, 2, 10, QLatin1Char('0'))
                      .arg(secs, 2, 10, QLatin1Char('0')) );
}

void ImportDialog::renderPreview(int percent)
{
    ui.currentProgress->setValue(percent);
    quint64 recived=0;//websnap.m_page.bytesReceived();
    quint64 B=1;
    QString f;
    quint64  KB = 1024 * B; //kilobyte
    quint64  MB = 1024 * KB; //megabyte
    quint64  GB = 1024 * MB; //gigabyte
    if (recived>GB)
        ui.downloaded->setText(f.sprintf("%1.2f GB",QVariant(recived/GB).toDouble())) ;
    else
        if (recived> MB)
            ui.downloaded->setText(f.sprintf("%1.2f MB",QVariant(recived/MB).toDouble()));
        else
            if (recived> KB)
                ui.downloaded->setText(f.sprintf("%1.2f KB",QVariant(recived/KB).toDouble()));
            else
                ui.downloaded->setText(f.sprintf("%1.2f bytes",QVariant(recived).toDouble()));

}

void ImportDialog::on_pushButton_clicked()
{
    int i=0;

    QTreeWidgetItemIterator it(ui.links, QTreeWidgetItemIterator::Checked);
    while (*it) {
        i++;
        ++it;
    }

    ui.totalProgress->setMaximum(i);
    ui.totalProgress->setValue(0);
    ui.currentProgress->setValue(0);
    ui.mainPage->hide();
    ui.progressPage->show();
    time.start();
    timer.start(1000);
    updateDisplay();
}
