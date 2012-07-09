#ifndef LINKSTREE_H
#define LINKSTREE_H

#include <QTreeWidget>
#include <engine.h>
#include <QDomNode>
#include <QTreeWidgetItem>
#include <QDropEvent>

class LinksTree : public QTreeWidget
{
     Q_OBJECT
public:
    explicit LinksTree(QWidget *parent = 0);
    enum Type{ Folder, Link};
    Q_DECLARE_FLAGS(Types, Type)
    inline void setEngine(Engine *engine){ m_engine = engine;}
    void buildTree(const QString &name);
    void refresh();
    QString currentText() const;

    void refreshSelected();
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent( QDropEvent *e );
    QDomElement parentDomItem(QTreeWidgetItem *item);
    bool removeItem(QTreeWidgetItem *item);
    QDomElement selectedDomItem();
    void addFolder(const QString &name);
    void addLink(QVariantMap items);
    void refreshItem(QTreeWidgetItem *item);

    inline int itemType(QTreeWidgetItem *item)
    { return item->data(0, 33).toInt();}

    inline int itemDomIndex(QTreeWidgetItem *item)
    { return item->data(0, 32).toInt();}

    inline bool isSelectionValid()
    { return (currentIndex().isValid() && currentItem()->isSelected());}

    inline int selectedItemType()
    { return isSelectionValid() ? itemType(currentItem()) : -1;}

    inline int selectedItemDomIndex()
    { return isSelectionValid() ? itemDomIndex(currentItem()) : -1;}

    inline QDomElement itemDomElement(QTreeWidgetItem *item)
    { return itemDomNode(item).toElement();}

    inline QDomNode itemDomNode(QTreeWidgetItem *item)
    { return m_engine->findNode(itemDomIndex(item), parentDomItem(item));}
    inline bool removeSelectedItem()
    { return isSelectionValid() ? removeItem(currentItem()) : false; }

signals:
    void folderSelected();//QTreeWidgetItem *item, int column
    void linkSelected();//QTreeWidgetItem *item, int column

private slots:
    void itemClicked(QTreeWidgetItem *item, int column);
private:
    Engine *m_engine;
    void addFolder(const QDomNode &node, int pos, QTreeWidgetItem *item);
    void addLink(const QDomNode &node, int pos, QTreeWidgetItem *item);
    void addItem(const QDomNode &node, int pos,QTreeWidgetItem *item );
    bool screenshortInToolTip;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(LinksTree::Types)
#endif // LINKSTREE_H
