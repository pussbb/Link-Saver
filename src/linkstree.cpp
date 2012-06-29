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

QDomElement LinksTree::parentDomItem(QTreeWidgetItem *item)
{
    if (currentItem()->parent() == NULL)
        return m_engine->documentRoot();

    QList<QTreeWidgetItem*> parents;
    QTreeWidgetItem *parent = currentItem()->parent();
    parents.append(parent);
    while(parent->parent() != NULL){
        parents.append(parent->parent());
    }

    QDomElement elem = m_engine->documentRoot() ;
    for (int i = parents.count() - 1; i >= 0; --i){
        elem = m_engine->findNode(itemDomIndex(parents.at(i)), elem).toElement();
    }

    return elem;
}

bool LinksTree::removeItem(QTreeWidgetItem *item)
{
    bool ok;
    if ( itemType(item) == LinksTree::Folder) {
        ok = m_engine->deleteDocumentFolder(itemDomIndex(item), parentDomItem(item));
    }
    if ( itemType(item) == LinksTree::Link) {

    }

    if (ok)
        delete item;
    return ok;
}

void LinksTree::itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    if ( itemType(item) == LinksTree::Folder) {
        emit(folderSelected());//item, column
        return;
    }
    if ( itemType(item) == LinksTree::Link) {
        emit(linkSelected());//item, column
    }
}

void LinksTree::addFolder(const QDomNode &node, int pos, QTreeWidgetItem *item)
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

void LinksTree::addLink(const QDomNode &node, int pos, QTreeWidgetItem *item)
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

void LinksTree::addItem(const QDomNode &node, int pos, QTreeWidgetItem *item)
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

