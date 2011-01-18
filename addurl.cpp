#include "addurl.h"
#include "ui_addurl.h"
#include <QTimer>
/////////////

WebCapture::WebCapture(): QObject(), m_zoom(100), m_percent(0)
{
    connect(&m_page, SIGNAL(loadProgress(int)), this, SLOT(showProgress(int)));
    connect(&m_page, SIGNAL(loadFinished(bool)), this, SLOT(saveResult(bool)));

}

void WebCapture::load(const QUrl &url, int zoom, const QString &outputFileName, int width)
{
    m_zoom = zoom;
    m_percent = 0;
    m_fileName = outputFileName;
    image = QImage();
    m_page.settings()->setAttribute(QWebSettings::JavaEnabled, false);
    m_page.settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, false);
    m_page.settings()->setAttribute(QWebSettings::LocalStorageEnabled, false);
    m_page.settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, false);
    m_page.settings()->setAttribute(QWebSettings::FrameFlatteningEnabled, false);
    m_page.settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    m_page.settings()->setAttribute(QWebSettings::PluginsEnabled, false);
    m_page.settings()->setAttribute(QWebSettings::SpatialNavigationEnabled, false);
    m_page.settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, false);
    m_page.mainFrame()->load(url);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    qreal factor = static_cast<qreal>(m_zoom) / 100.0;
#if QT_VERSION < 0x040500
    m_page.setViewportSize(QSize(width, 3 * width / 4) / factor);
#else
    m_page.mainFrame()->setZoomFactor(factor);///width, 3 * width / 4
    m_page.setViewportSize(QSize(width, width / 2));
#endif

}

void WebCapture::showProgress(int percent)
{
    if (m_percent >= percent)
        return;
}

void WebCapture::saveResult(bool ok)
{
    //std::cout << std::endl;

    // crude error-checking
    if (!ok) {
        ///std::cerr << "Failed loading " << qPrintable(m_page.mainFrame()->url().toString()) << std::endl;
        emit finished();
        return;
    }

    // create the image for the buffer
    QSize size = m_page.mainFrame()->contentsSize();
    //prevent memory leek when generating big page
    if(size.height()>2000)
        size.rheight()=2000;
    if(size.width()>1500)
        size.rwidth()=1500;
    image = QImage(size, QImage::Format_RGB444);
    image.fill(Qt::transparent);

    // render the web page
    QPainter p(&image);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    // size.rheight()=500;
    //  size.rwidth()=1024;

    qDebug()<<size;
    m_page.setViewportSize(size);
    m_page.mainFrame()->render(&p);
    p.end();

#if QT_VERSION < 0x040500
    // scale, since we don't have full page zoom
    qreal factor = static_cast<qreal>(m_zoom) / 100.0;
    image = image.scaled(size * factor, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
#endif

    image.save(m_fileName);
    image = QImage();
    emit finished();
}
#define tmpdir QDir::toNativeSeparators ( QDir::tempPath()+"/" )
#define imgdir QDir::toNativeSeparators (QApplication::applicationDirPath()+"/images/" )
AddUrl::AddUrl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUrl)
{
    ui->setupUi(this);
    connect(&websnap.m_page, SIGNAL(loadProgress(int)), this, SLOT(renderPreview(int)));
    QObject::connect(&websnap, SIGNAL(finished()), this, SLOT(Preview()));
    p=new QProgressDialog(this);
    ui->preview->setScaledContents(true);
    this->changed=false;
}

AddUrl::~AddUrl()
{
    delete ui;
}

void AddUrl::load(QString url)
{
    fname=QString(QCryptographicHash::hash(url.toLocal8Bit(),QCryptographicHash::Md5).toHex())+".png";

    p->setModal(true);
    p->setLabelText(tr("Generating image"));
    p->setMaximum(100);
    p->show();
    ui->url_edit->setText(url);
    this->url=url;
    this->changed=true;
    websnap.load( guessUrlFromString(url.toLatin1().data()), 100, tmpdir+fname, 1024);

}

void AddUrl::additem(QString name, int index, bool current )
{
    ui->comboBox->addItem(name,index);
    if(current)
    {
        ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
    }
}

void AddUrl::set_Data(QString str,int index)
{
    switch(index)
    {
    case 1:
    {
        ui->url_edit->setText(str);
        break;
    }
    case 2:
    {
        ui->lineEdit->setText(str);
        break;
    }
    case 3:
    {
        ui->preview->setPixmap(QPixmap::fromImage(QImage(str)));
        break;
    }
    case 4:
    {
        this->fname=str;
        break;
    }
    default:
    {
        break;
    }
    }
}

void AddUrl::renderPreview(int percent)
{

    p->setValue(percent);
}
void AddUrl::Preview()
{
    p->close();
    QPixmap resized;
    QPixmap origin(tmpdir+fname);
    if(origin.height()>=1600){
        origin = origin.copy(0,0,origin.width(),origin.width()/1.2);
        // origin.scaled(origin.width()/1.4,origin.width()/1.8,Qt::IgnoreAspectRatio,Qt::FastTransformation );
    }
    resized = origin.scaled(origin.width()/1.5,origin.width()/1.9,Qt::KeepAspectRatio,Qt::FastTransformation );
    //scaledToWidth(origin.width()/1.4);//
    resized.save(tmpdir+fname);

    ui->lineEdit->setText(websnap.m_page.mainFrame()->evaluateJavaScript("document.title").toString()) ;
    title=ui->lineEdit->text();
    ui->preview->setPixmap(QPixmap::fromImage(QImage(tmpdir+fname)));
}
QVariant AddUrl::get_cat()
{
    return ui->comboBox->itemData(ui->comboBox->currentIndex(),32);
}

//renderPreview(100);
void AddUrl::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AddUrl::on_lineEdit_textChanged(QString )
{
    title=ui->lineEdit->text();
}

void AddUrl::on_url_edit_textChanged(QString )
{
    this->url=ui->url_edit->text();
    if(this->isVisible() && !p->isVisible())
    {
        this->load(ui->url_edit->text());
    }

}

