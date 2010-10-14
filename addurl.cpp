#include "addurl.h"
#include "ui_addurl.h"
/////////////

WebCapture::WebCapture(): QObject(), m_zoom(100), m_percent(0)
{
    connect(&m_page, SIGNAL(loadProgress(int)), this, SLOT(showProgress(int)));
    connect(&m_page, SIGNAL(loadFinished(bool)), this, SLOT(saveResult(bool)));

}

void WebCapture::load(const QUrl &url, int zoom, const QString &outputFileName, int width)
{
   // std::cout << "Loading " << qPrintable(url.toString()) << std::endl;
    m_zoom = zoom;
    m_percent = 0;
    m_fileName = outputFileName;
    image = QImage();
    m_page.mainFrame()->load(url);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    m_page.mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    qreal factor = static_cast<qreal>(m_zoom) / 100.0;
#if QT_VERSION < 0x040500
    m_page.setViewportSize(QSize(width, 3 * width / 4) / factor);
#else
    m_page.mainFrame()->setZoomFactor(factor);
    m_page.setViewportSize(QSize(width, 3 * width / 4));
#endif

}

void WebCapture::showProgress(int percent)
{
    if (m_percent >= percent)
        return;

    //while (m_percent++ < percent)
       // std::cout << "#" << std::flush;
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
    image = QImage(size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    // render the web page
    QPainter p(&image);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    m_page.setViewportSize(m_page.mainFrame()->contentsSize());
    m_page.mainFrame()->render(&p);
    p.end();

#if QT_VERSION < 0x040500
    // scale, since we don't have full page zoom
    qreal factor = static_cast<qreal>(m_zoom) / 100.0;
    image = image.scaled(size * factor, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
#endif

    image.save(m_fileName);
    emit finished();
}

// shamelessly copied from Qt Demo Browser
static QUrl guessUrlFromString(const QString &string)
{
   QString urlStr = string.trimmed();
   QRegExp test(QLatin1String("^[a-zA-Z]+\\:.*"));

   // Check if it looks like a qualified URL. Try parsing it and see.
   bool hasSchema = test.exactMatch(urlStr);
   if (hasSchema) {
       QUrl url(urlStr, QUrl::TolerantMode);
       if (url.isValid())
           return url;
   }

   // Might be a file.
   if (QFile::exists(urlStr))
       return QUrl::fromLocalFile(urlStr);

   // Might be a shorturl - try to detect the schema.
   if (!hasSchema) {
       int dotIndex = urlStr.indexOf(QLatin1Char('.'));
       if (dotIndex != -1) {
           QString prefix = urlStr.left(dotIndex).toLower();
           QString schema = (prefix == QLatin1String("ftp")) ? prefix : QLatin1String("http");
           QUrl url(schema + QLatin1String("://") + urlStr, QUrl::TolerantMode);
           if (url.isValid())
               return url;
       }
   }

   // Fall back to QUrl's own tolerant parser.
   return QUrl(string, QUrl::TolerantMode);
}
////////////
#define tmpdir QDir::toNativeSeparators ( QDir::tempPath()+"/" )
#define imgdir QDir::toNativeSeparators (QApplication::applicationDirPath()+"/images/" )
AddUrl::AddUrl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUrl)
{
    ui->setupUi(this);
   //websnap = new WebCapture(this);
    //connect(websnap, SIGNAL(progress(int)), this, SLOT(renderPreview(int)));
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
{p->close();



 QPixmap resized;
 QPixmap origin(tmpdir+fname);
 if(origin.height()>=1600){
 origin = origin.copy(0,0,origin.width(),origin.width()/1.2);// origin.scaled(origin.width()/1.4,origin.width()/1.8,Qt::IgnoreAspectRatio,Qt::FastTransformation );
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

