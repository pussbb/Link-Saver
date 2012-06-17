
#include "webpage.h"

#include <qglobal.h>

QList<QString> webPage::agentList_ = QList<QString> ()
    <<"Opera/9.63 (Windows NT 6.0; U; ru) Presto/2.1.1"
    << "Opera/9.80 (X11; Linux i686; U; ru) Presto/2.6.30 Version/10.61"
    << "Opera/9.80 (Windows NT 6.1; U; it) Presto/2.6.30 Version/10.63"
    << "Opera/9.80 (Windows NT 5.1; U; en) Presto/2.6.37 Version/11.00"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.1) Gecko/20090624 Firefox/3.5"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/534.6 (KHTML like Gecko) Chrome/7.0.503.0 Safari/534.6"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; pl; rv:1.9.2.11) Gecko/20101012 Firefox/3.6.11"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; it; rv:1.9.0.16) Gecko/2010021013 Firefox/3.0.16 Flock/2.5.6"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/534.7 (KHTML like Gecko) Chrome/7.0.517.41 Safari/534.7"
    << "Mozilla/5.0 (Windows; U; Windows NT 5.1; cs; rv:1.9.1.14) Gecko/20101001 Firefox/3.5.14"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.0; en-US; rv:1.7.13) Gecko/20050610 K-Meleon/0.9"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-GB; rv:1.9.2.10) Gecko/20100914 Firefox/3.6.10"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.1; de; rv:1.9.2.11) Gecko/20101012 AskTbSPC2/3.8.0.12304 Firefox/3.6.11"
    << "Mozilla/5.0 (Windows; U; Windows NT 6.1; de-DE) AppleWebKit/533.18.1 (KHTML like Gecko) Version/5.0.2 Safari/533.18.5"
    << "Mozilla/5.0 (Windows NT 5.1; U; en; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6"
    << "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; WOW64; SLCC1; .NET CLR 2.0.50727; .NET CLR 3.0.04506; Media Center PC 5.0)"
    << "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)"
    << "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_5_6; en-us) AppleWebKit/525.27.1 (KHTML like Gecko) Version/3.2.1 Safari/525.27.1"
    << "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.1.2) Gecko/20070221 SeaMonkey/1.1.1"
    << "Mozilla/5.0 (X11; U; Linux i686 (x86_64); en-US; rv:1.8.1.6) Gecko/2007072300 Iceweasel/2.0.0.6 (Debian-2.0.0.6-0etch1+lenny1)"
    << "Mozilla/5.0 (X11; U; Linux x86_64; en-US) AppleWebKit/534.10 (KHTML like Gecko) Chrome/8.0.552.11 Safari/534.10"
    << "Mozilla/5.0 (X11; U; Linux x86_64; de; rv:1.9.2.11) Gecko/20101013 Ubuntu/10.10 (maverick) Firefox/3.6.11"
    << "Mozilla/5.0 (X11; U; Linux i686; it; rv:1.9.2.10) Gecko/20100915 Ubuntu/10.04 (lucid) Firefox/3.6.10 GTB7.1"
    << "Mozilla/5.0 (X11; U; Linux i686; it-it) AppleWebKit/531.2+ (KHTML like Gecko) Safari/531.2+ Epiphany/2.30.6"
    << "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.2.11) Gecko/20101013 Ubuntu/10.04 (lucid) Firefox/3.6.11"
    << "Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.5 (like Gecko) (Debian|Debian)"
    << "Mozilla/5.0 (Linux; U; Android 2.1-update1; ru-ru; GT-I9000 Build/ECLAIR) AppleWebKit/530.17 (KHTML like Gecko) Version/4.0 Mobile Safari/530.17"
    << "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_4; en-us) AppleWebKit/533.18.1 (KHTML like Gecko) Version/5.0.2 Safari/533.18.5"
    << "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; it; rv:1.9.2.11) Gecko/20101012 Firefox/3.6.11";

webPage::webPage()
    : QWebPage()
{
    resetUserAgent();
}

void webPage::resetUserAgent()
{
    const int low = 0;
    const int high = webPage::agentList_.size() - 1;
    const int random = qrand() % ((high + 1) - low) + low;
    currentAgent_ = webPage::agentList_[ random ];
}

QString webPage::userAgentForUrl(const QUrl &) const
{
    return currentAgent_;
}
