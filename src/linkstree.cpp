#include "linkstree.h"


LinksTree::LinksTree(QWidget *parent) :
    QTreeWidget(parent)
{
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(itemClicked(QTreeWidgetItem*,int)));
    setContextMenuPolicy( Qt::CustomContextMenu);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDefaultDropAction(Qt::MoveAction);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDropIndicatorShown(true);
}

void LinksTree::buildTree(const QString &name)
{
    m_engine->setCurrent(name);
    refresh();
}

#include <QSettings>
void LinksTree::refresh()
{
    clear();
    QSettings settings;
    screenshortInToolTip = settings.value("App/screenshortInToolTip").toBool();

    QDomNodeList nodes = m_engine->documentRoot().childNodes();
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

void LinksTree::refreshSelected()
{
    if ( ! isSelectionValid())
        return refresh();

    refreshItem(currentItem());
}

void LinksTree::dragMoveEvent(QDragMoveEvent *e)
{
    QTreeWidgetItem *item = itemAt(e->pos());
    if ( ! item)
        return e->accept();

    if ( itemType(item) == LinksTree::Link)
        return e->ignore();

    return e->accept();
}

void LinksTree::dropEvent(QDropEvent *e)
{
    QTreeWidgetItem *item = itemAt(e->pos());

    if (item != NULL)
        m_engine->moveItem(itemDomElement(item), itemDomElement(currentItem()));
    else
        m_engine->moveItem(m_engine->documentRoot(), itemDomElement(currentItem()));

    QTreeWidget::dropEvent(e);
}

QDomElement LinksTree::parentDomItem(QTreeWidgetItem *item)
{
    if (item->parent() == NULL)
        return m_engine->documentRoot();

    QList<QTreeWidgetItem*> parents;
    QTreeWidgetItem *parent = item->parent();
    parents.append(parent);
    while((parent = parent->parent()) != NULL){
        parents.append(parent);
    }

    QDomElement elem = m_engine->documentRoot() ;
    for (int i = parents.count() - 1; i >= 0; --i){
        elem = m_engine->findNode(itemDomIndex(parents.at(i)), elem).toElement();
    }

    return elem;
}

bool LinksTree::removeItem(QTreeWidgetItem *item)
{
    bool ok = true;
    if ( itemType(item) == LinksTree::Folder) {
        ok = m_engine->deleteDocumentFolder(itemDomIndex(item), parentDomItem(item));
    }
    if ( itemType(item) == LinksTree::Link) {
        ok = m_engine->deleteDocumentLink(itemDomIndex(item), parentDomItem(item));
    }

    if (ok)
        delete item;
    return ok;
}

QDomElement LinksTree::selectedDomItem()
{
    if ( ! isSelectionValid())
        return m_engine->documentRoot();
    return itemDomElement(currentItem());
}

void LinksTree::addFolder(const QString &name)
{
    if ( isSelectionValid() && itemType(currentItem()) != LinksTree::Folder) {
        QTreeWidgetItem *parent;
        if ( (parent = currentItem()->parent()) != NULL
             && itemType(parent) == LinksTree::Folder) {
            m_engine->addFolder(itemDomElement(parent), name);
            refreshItem(parent);
        }
        else {
            m_engine->addFolder( m_engine->documentRoot(), name);
            refresh();
        }
        return;
    }
    else if (isSelectionValid()){
        m_engine->addFolder(selectedDomItem(), name);
        refreshSelected();
        return;
    }
    m_engine->addFolder( m_engine->documentRoot(), name);
    refresh();
}

void LinksTree::addLink(QVariantMap items)
{
    if ( isSelectionValid() && itemType(currentItem()) != LinksTree::Folder) {
        QTreeWidgetItem *parent;
        if ( (parent = currentItem()->parent()) != NULL
             && itemType(parent) == LinksTree::Folder) {
            m_engine->addLink(itemDomElement(parent), items);
            refreshItem(parent);
        }
        else {
            m_engine->addLink( m_engine->documentRoot(), items);
            refresh();
        }
        return;
    }
    else if (isSelectionValid()){
        m_engine->addLink(selectedDomItem(), items);
        refreshSelected();
        return;
    }
    m_engine->addLink( m_engine->documentRoot(), items);
    refresh();
}

void LinksTree::refreshItem(QTreeWidgetItem *item)
{
    qDeleteAll(item->takeChildren());
    QDomNodeList nodes = itemDomElement(item).childNodes();

    if ( nodes.count() == 0)
        return;

    for(int i=0; i < nodes.count(); ++i)
    {
        addItem(nodes.at(i), i, item);
    }
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
    _item->setText(0, Engine::nodeData(node, Engine::Title));
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
    _item->setText(0, Engine::nodeData(node, Engine::Title));
    _item->setData(0, 32, pos);
    _item->setData(0, 33, LinksTree::Link);
    _item->setData(0, 34, Engine::nodeData(node, Engine::Url));
    _item->setIcon(0, QIcon(":/link"));
    if (screenshortInToolTip) {
        QImage image(m_engine->documentImagesPath() + Engine::nodeData(node, Engine::Screenshort));
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
        QString tooltip = QString("<img src=\"data:image/png;base64,%1\" width=\"250\" height=\"150\"></img>")
                .arg(QString(buffer.data().toBase64()));
        _item->setToolTip(0, tooltip);
    }

    if ( item != NULL)
        item->addChild(_item);
    else
        addTopLevelItem(_item);
}

void LinksTree::addItem(const QDomNode &node, int pos, QTreeWidgetItem *item)
{
    if ( Engine::nodeType(node) == Engine::Folder)
    {
        addFolder(node, pos, item);
    }
    if ( Engine::nodeType(node) == Engine::Link) {
        addLink(node, pos, item);
    }
}

