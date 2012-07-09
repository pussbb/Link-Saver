#ifndef LINKSFLOW_H
#define LINKSFLOW_H

#include <pictureflow/pictureflow.h>
#include <QKeyEvent>
#include <QDomNode>

class LinksFlow : public PictureFlow
{
    Q_OBJECT
public:
    explicit LinksFlow();
    void keyPressEvent(QKeyEvent* event) ;
public slots:
    void show(QDomNode node, const QString &imagePath);
    void folderClicked(QDomNode node);
private:
    QString _imagePath;
    void buildFlow(QDomNode node);
};

#endif // LINKSFLOW_H
