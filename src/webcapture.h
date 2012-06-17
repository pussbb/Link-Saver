#ifndef WEBCAPTURE_H
#define WEBCAPTURE_H

#include "webpage.h"
#include <QPointer>
#include <QProgressBar>

class WebCapture : public QObject
{
    Q_OBJECT

public:
    WebCapture(QObject *parent = 0);
    void load(const QUrl &url);
    void load(const QString &url);
    void image(const QString &outputFileName, int width, int height ,int zoom);
    inline QWebFrame * frame(){return page_.mainFrame();}
    static QUrl guessUrlFromString(const QString &string);
    static bool validUrl(const QString &string);
    inline void setProgressBar(QProgressBar *bar) { progress = bar;}
signals:
    void finished(bool);

private slots:
    void saveResult(bool ok);
    void showProgress(int percent);
private:
    webPage page_;
    QPointer<QProgressBar> progress;
    int zoom_;
};


#endif // WEBCAPTURE_H
