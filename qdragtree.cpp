#include <QtGui>
#include "qdragtree.h"

QDragTree::QDragTree(QWidget *parent) :
    QTreeWidget(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}
void QDragTree::dropEvent( QDropEvent *e )
{
    emit dropted(from_index,to_index,item_index);
    QTreeWidget::dropEvent(e);
}
void QDragTree::dragMoveEvent(QDragMoveEvent *e)
{
    QTreeWidgetItem *item = itemAt(e->pos());

    bool accept = false;

    if (item)
    {
        if (item->childCount()>0 || item->data(0,33).toString()=="folder")
        {
            accept = true;
            from_index=currentIndex().parent().data(Qt::UserRole).toInt();
            to_index=item->data(0,Qt::UserRole).toInt();
            item_index=currentIndex().data(Qt::UserRole).toInt();
        }
    }

    if ( accept )
    {
        e->accept();
    }
    else
    {
        e->ignore();
    }
}


