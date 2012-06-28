#include "linkstree.h"


LinksTree::LinksTree(QWidget *parent) :
    QTreeWidget(parent)
{
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(itemClicked(QTreeWidgetItem*,int)));
    setContextMenuPolicy( Qt::CustomContextMenu);
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
        addItem(nodes.at(i), i, NULL);
    }
}

QString LinksTree::currentText() const
{
    if ( currentIndex().isValid())
        return currentItem()->text(0);
    return QString();
}

int LinksTree::selectedItemType()
{
    if ( currentIndex().isValid() && currentItem()->isSelected())
        return currentItem()->data(0, 33).toInt();
    return -1;
}

int LinksTree::selectedItemDomIndex()
{
    if ( currentIndex().isValid() && currentItem()->isSelected())
        return currentItem()->data(0, 32).toInt();
    return -1;
}


void LinksTree::itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    if ( item->data(0, 33).toInt() == LinksTree::Folder) {
        emit(folderSelected());//item, column
        return;
    }
    if ( item->data(0, 33).toInt() == LinksTree::Link) {
        emit(linkSelected());//item, column
    }
}

void LinksTree::addFolder(const QDomNode &node, int &pos, QTreeWidgetItem *item)
{

    QTreeWidgetItem *_item = new QTreeWidgetItem();
    _item->setText(0, node.toElement().attribute("name"));
    _item->setData(0, 32, pos);
    _item->setData(0, 33, LinksTree::Folder);
    _item->setIcon(0, QIcon(":/folder"));

    if ( item != NULL)
        item->addChild(_item);
    else
        addTopLevelItem(_item);

    QDomNodeList nodes =node.childNodes();
    if ( nodes.count() == 0)
        return;

    for(int i=0; i < nodes.count(); ++i)
    {
        addItem(nodes.at(i), i, _item);
    }
}

void LinksTree::addLink(const QDomNode &node, int &pos, QTreeWidgetItem *item)
{
    QTreeWidgetItem *_item=new QTreeWidgetItem();
    _item->setText(0, node.firstChildElement("title").toElement().text());
    _item->setData(0, 32, pos);
    _item->setData(0, 33, LinksTree::Link);
    _item->setData(0, 34, node.firstChildElement("url").toElement().text());
    _item->setIcon(0, QIcon(":/link"));

    if ( item != NULL)
        item->addChild(_item);
    else
        addTopLevelItem(_item);
}

void LinksTree::addItem(const QDomNode &node, int &pos, QTreeWidgetItem *item)
{
    if ( node.nodeName() == "folder")
    {
        addFolder(node, pos, item);
    }
    if ( node.nodeName() == "bookmark"
         && node.toElement().attribute("type") == "link") {
        addLink(node, pos, item);
    }
}
