#include "linkdialog.h"
#include "ui_linkdialog.h"
#include <QSettings>
#include <QClipboard>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDir>

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

QVariantMap LinkDialog::getData() const
{
    QVariantMap result;
    result.insert("url", ui->url->text());
    result.insert("title", ui->title->text());
    result.insert("absoluteFileName", QDir::tempPath() +"/"+ fileName );
    result.insert("screenshort", fileName);
    return result;
}

void LinkDialog::setElement(const QDomElement &element, const QString &imgPath)
{
    ui->url->setText(Engine::nodeData(element,Engine::Url));
    ui->title->setText(Engine::nodeData(element,Engine::Title));
    fileName = Engine::nodeData(element,Engine::Screenshort);
    previewUpdate(imgPath+fileName);
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

void LinkDialog::saveImave(bool)
{
    fileName = QCryptographicHash::hash(ui->url->text().toLocal8Bit(),QCryptographicHash::Md5).toHex() + ".png";
    QFileInfo fi (QDir::tempPath() +"/"+ fileName);

    if (fi.exists())
        QFile::remove(fi.absoluteFilePath());

    capture->image(fi.absoluteFilePath(), ui->width->value(), ui->height->value(), ui->zoom->value());
    previewUpdate(fi.absoluteFilePath());

    if (ui->title->text().isEmpty())
    {
        QString title = capture->frame()->documentElement().findFirst("title").toPlainText();
        ui->title->setText(title);
    }
}

void LinkDialog::previewUpdate(const QString &image)
{
    QPixmap pixmap = QPixmap::fromImage(QImage(image));
    pixmap = pixmap.scaledToHeight(ui->preview->height());
    pixmap = pixmap.scaledToWidth(ui->preview->width());
    ui->preview->setPixmap(pixmap);
}
