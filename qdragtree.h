#ifndef QDRAGTREE_H
#define QDRAGTREE_H

#include <QTreeWidget>

class QDragTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit QDragTree(QWidget *parent = 0);

    void dropEvent( QDropEvent *e );

    void dragMoveEvent(QDragMoveEvent *e);
    int from_index;
    int to_index;
    int item_index;
signals:
    void dropted(int from,int to,int item);
public slots:

};

#endif // QDRAGTREE_H
