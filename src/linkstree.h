#ifndef LINKSTREE_H
#define LINKSTREE_H

#include <QTreeWidget>
#include <engine.h>
#include <QDomNode>


class LinksTree : public QTreeWidget
{
     Q_OBJECT
public:
    explicit LinksTree(QWidget *parent = 0);
    inline void setEngine(Engine *engine){ m_engine = engine;}
    void buildTree(const QString &name);
    void refresh();
private:
    Engine *m_engine;
};

#endif // LINKSTREE_H
