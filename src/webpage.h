#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebPage>

class webPage : public QWebPage
{
    public:
        webPage();
        QString userAgentForUrl(const QUrl &url ) const;

        void resetUserAgent();

    private:
        QString currentAgent_;
        static QList<QString> agentList_;
};

#endif // WEBPAGE_H
