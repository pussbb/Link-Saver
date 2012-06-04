#include "linkstree.h"

LinksTree::LinksTree(QWidget *parent) :
    QTreeWidget(parent)
{

}

void LinksTree::buildTree(const QString &name)
{
    m_doc = m_engine->document(name);
    qDebug()<< m_doc.documentElement().tagName();
}
