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
        QDomNode node = nodes.at(i);
        if ( node.nodeName() == "folder")
        {
            QTreeWidgetItem *item=new QTreeWidgetItem(this);
            item->setText(0, node.toElement().attribute("name"));
            item->setData(0, 32, i);
            item->setData(0, 33, LinksTree::Folder);
            item->setIcon(0, QIcon(":/folder"));
            addTopLevelItem(item);
        }
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
