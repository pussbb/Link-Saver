#include "linkstree.h"


LinksTree::LinksTree(QWidget *parent) :
    QTreeWidget(parent)
{

}

void LinksTree::buildTree(const QString &name)
{
    m_engine->setCurrent(name);
    refresh();
}

void LinksTree::refresh()
{
    clear();
    QDomNodeList nodes=  m_engine->documentRoot().childNodes();
    if ( nodes.count() == 0)
        return;

    for(int i=0; i < nodes.count(); ++i)
    {
        QDomNode node = nodes.at(i);
        if ( node.nodeName() == "folder")
        {
            QTreeWidgetItem *item=new QTreeWidgetItem(this);
            item->setText(0, node.toElement().attribute("name"));
            item->setData(0,32,i);
            item->setData(0,33,"folder");
            item->setIcon(0,QIcon(":/folder"));
            addTopLevelItem(item);
        }
    }

}
