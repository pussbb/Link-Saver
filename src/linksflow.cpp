#include "linksflow.h"

LinksFlow::LinksFlow() :
    PictureFlow()
{
    int ww = width();
    int wh = height();
    int dim = (ww > wh) ? wh : ww;
    dim = dim * 3 / 4;
    setSlideSize(QSize(3*dim / 5, dim));
    setBackgroundColor(QColor(88,84,84,125));
    connect(this,SIGNAL(folderClicked(QDomNode)),
             this, SLOT(folderClicked(QDomNode)));
}

void LinksFlow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape
            || event->key() == Qt::Key_Enter
            || event->key() == Qt::Key_Return) {
        event->accept();
        close();
    }
    if (event->key() == Qt::Key_F11) {
        if (event->modifiers() == Qt::AltModifier) {
            switch (reflectionEffect()) {
                //case NoReflection:      setReflectionEffect(PlainReflection); break;
            case PlainReflection:   setReflectionEffect(BlurredReflection); break;
            case BlurredReflection: setReflectionEffect(PlainReflection); break;
            default:                setReflectionEffect(PlainReflection); break;
            }
            event->accept();
            return;
        }
    }
    PictureFlow::keyPressEvent(event);
}

#include <engine.h>

void LinksFlow::show(QDomNode node, const QString &imagePath)
{
    _imagePath = imagePath;
    clear();
    buildFlow(node);
    QWidget::show();

    showFullScreen();
}

void LinksFlow::folderClicked(QDomNode node)
{

    if ( node.isNull())
        return;
    clear();
    buildFlow(node);
}

void LinksFlow::buildFlow(QDomNode node)
{

    if ( node.isNull())
        return;

    QImage img;
    QDomNode parent = node.parentNode();
    if ( ! parent.isNull() && parent.nodeName() != "lsbook")
    {
        img.load(":folder_up");
        addSlide(img, parent, true);
    }
    QDomNodeList nodes = node.childNodes();
    for(int i = 0; i < nodes.count(); i++) {
        QDomNode _node = nodes.item(i);
        if (_node.isNull())
            continue;
        bool isFolder = (Engine::nodeType(_node) == Engine::Folder);
        if (isFolder) {
            img.load(":folder_up");
        }
        else if ( Engine::nodeType(_node) == Engine::Link) {
            img.load(_imagePath + Engine::nodeData(_node, Engine::Screenshort));
        }
        addSlide(img, _node, isFolder);
    }
}
