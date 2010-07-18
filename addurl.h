#ifndef ADDURL_H
#define ADDURL_H

#include <QDialog>
#include <QtGui>
#include <QtWebKit>
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
 QProgressDialog *p;
void additem(QString name,int index);
QVariant get_cat();
protected:
    void changeEvent(QEvent *e);

private slots:
    void renderPreview(int percent);
    void Preview();
private:
    Ui::AddUrl *ui;
};

#endif // ADDURL_H
