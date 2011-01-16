#ifndef ADDURL_H
#define ADDURL_H

#include <QDialog>
// ==== WebSnap: capture a web page and create a thumbnail preview ====
#include <QtGui>
#include <QtWebKit>
#include <QProgressDialog>
class WebCapture : public QObject
{
    Q_OBJECT

public:
    QImage image;
    WebCapture();
    void load(const QUrl &url, int zoom, const QString &outputFileName, int width);
        QWebPage m_page;
        QString m_fileName;
        int m_zoom;
        int m_percent;


signals:
    void finished();

private slots:
    void showProgress(int percent);
    void saveResult(bool ok);

private:
//    QWebPage m_page;
//    QString m_fileName;
//    int m_zoom;
//    int m_percent;
};


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

/////////////////////////////////////////////////////
namespace Ui {
    class AddUrl;
}

class AddUrl : public QDialog {
    Q_OBJECT
public:
    explicit AddUrl(QWidget *parent = 0);
    ~AddUrl();
void load(QString url);
 WebCapture websnap;
 QString fname;
 QString title;
 QString url;
 bool changed;
 QProgressDialog *p;
void additem(QString name,int index,bool current = false);
void set_Data(QString str,int index);
QVariant get_cat();
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_url_edit_textChanged(QString );
    void on_lineEdit_textChanged(QString );
    void renderPreview(int percent);
    void Preview();
private:
    Ui::AddUrl *ui;
};

#endif // ADDURL_H
