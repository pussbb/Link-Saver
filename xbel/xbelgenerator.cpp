/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "xbelgenerator.h"

XbelGenerator::XbelGenerator(QDomDocument *doc) : doc(doc)
{

}

bool XbelGenerator::write(QIODevice *device)
{
    out.setDevice(device);
    out.setCodec("UTF-8");
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        << "<!DOCTYPE xbel>\n"
        << "<xbel version=\"1.0\">\n";

    QDomElement docElem = doc->documentElement();

    for(int i=0;i<docElem.childNodes().count();i++)
    {
        generateItem(docElem.childNodes().item(i).toElement(), 1);
    }
   // for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
    //    generateItem(treeWidget->topLevelItem(i), 1);

    out << "</xbel>\n";
    return true;
}

QString XbelGenerator::indent(int depth)
{
    const int IndentSize = 4;
    return QString(IndentSize * depth, ' ');
}

QString XbelGenerator::escapedText(const QString &str)
{
    QString result = str;
    result.replace("&", "&amp;");
    result.replace("<", "&lt;");
    result.replace(">", "&gt;");
    return result;
}

QString XbelGenerator::escapedAttribute(const QString &str)
{
    QString result = escapedText(str);
    result.replace("\"", "&quot;");
    result.prepend("\"");
    result.append("\"");
    return result;
}

void XbelGenerator::generateItem(QDomElement item, int depth)
{
    QString tagName = item.tagName();
    QString tagType = item.attributeNode("url").value();
    if (tagName == "folder") {

        out << indent(depth) << "<folder folded=\"yes"
                             << "\">\n"
            << indent(depth + 1) << "<title>" << escapedText(item.attribute("name"))
                                 << "</title>\n";

        for (int i = 0; i <  item.childNodes().count(); ++i)
            generateItem(item.childNodes().item(i).toElement(), depth + 1);

        out << indent(depth) << "</folder>\n";
    } else if (tagName == "bookmark" && tagType!="app") {
        out << indent(depth) << "<bookmark";
        if (!item.text().isEmpty())
            out << " href=" << escapedAttribute(tagType);
        out << ">\n"
            << indent(depth + 1) << "<title>" << escapedText(item.text())
                                 << "</title>\n"
            << indent(depth) << "</bookmark>\n";
    } else if (tagName == "separator") {
        out << indent(depth) << "<separator/>\n";
    }
}
