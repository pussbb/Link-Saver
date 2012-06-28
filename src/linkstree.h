#ifndef LINKSTREE_H
#define LINKSTREE_H

#include <QTreeWidget>
#include <engine.h>
#include <QDomNode>
#include <QTreeWidgetItem>

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
    int selectedItemType();
    int selectedItemDomIndex();
signals:
    void folderSelected();//QTreeWidgetItem *item, int column
    void linkSelected();//QTreeWidgetItem *item, int column

private slots:
    void itemClicked(QTreeWidgetItem *item, int column);
private:
    Engine *m_engine;
    void addFolder(const QDomNode &node, int &pos, QTreeWidgetItem *item);
    void addLink(const QDomNode &node, int &pos, QTreeWidgetItem *item);
    void addItem(const QDomNode &node, int &pos,QTreeWidgetItem *item );
};

Q_DECLARE_OPERATORS_FOR_FLAGS(LinksTree::Types)
#endif // LINKSTREE_H
