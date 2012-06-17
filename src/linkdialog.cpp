#include "linkdialog.h"
#include "ui_linkdialog.h"
#include <QSettings>
#include <QClipboard>
#include <QMessageBox>

#include <QDebug>


LinkDialog::LinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkDialog)
{
    ui->setupUi(this);
    capture = new WebCapture(this);
    capture->setProgressBar(ui->progress);

    QClipboard* clipboard = QApplication::clipboard();
    if ( WebCapture::validUrl(clipboard->text(QClipboard::Clipboard))) {
        ui->url->setText(clipboard->text(QClipboard::Clipboard));
    }

    QObject::connect(capture, SIGNAL(finished(bool)), this, SLOT(saveImave(bool)));

    QSettings settings;
    int width = settings.value("links.width", 340).toInt();
    int height = settings.value("links.height", 250).toInt();
    int zoom = settings.value("links.zoom", 60).toInt();

    ui->width->setValue(width);
    ui->height->setValue(height);
    ui->zoom->setValue(zoom);
    ui->progress->setVisible(false);
}

LinkDialog::~LinkDialog()
{
    capture->deleteLater();
    delete ui;
}

void LinkDialog::on_toolButton_clicked()
{
    if ( ! WebCapture::validUrl(ui->url->text())) {
        QMessageBox::warning(0,  QObject::tr("Url"),
                             QObject::tr("Must be valid url adrress"));
        return;
    }

    capture->load(ui->url->text());
}

#include <QCryptographicHash>
#include <QDir>

void LinkDialog::saveImave(bool)
{
    fileName = QCryptographicHash::hash(ui->url->text().toLocal8Bit(),QCryptographicHash::Md5).toHex() + ".png";
    QFileInfo fi (QDir::tempPath() +"/"+ fileName);

    if (fi.exists())
        QFile::remove(fi.absoluteFilePath());

    capture->image(fi.absoluteFilePath(), ui->width->value(), ui->height->value(), ui->zoom->value());
    QPixmap pixmap = QPixmap::fromImage(QImage(fi.absoluteFilePath()));
    pixmap = pixmap.scaledToHeight(ui->preview->height());
    pixmap = pixmap.scaledToWidth(ui->preview->width());
    ui->preview->setPixmap(pixmap);
}
