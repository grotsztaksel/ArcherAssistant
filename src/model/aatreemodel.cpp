#include "aatreemodel.h"

#include <QDebug>
AATreeModel::AATreeModel(QObject* parent) : QAbstractItemModel(parent) {
  m_rootNode = new AATreeNode_pugi(this, true);
}

AATreeModel::~AATreeModel() {
  m_rootNode->deleteLater();
}

QVariant AATreeModel::headerData(int section,
                                 Qt::Orientation orientation,
                                 int role) const {
  return QVariant(QString("header"));
}

QModelIndex AATreeModel::index(int row,
                               int column,
                               const QModelIndex& parent) const {
  qDebug() << "index" << row << column;
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  AATreeNode_abstract* parentItem;
  if (!parent.isValid())
    parentItem = m_rootNode;
  else
    parentItem = static_cast<AATreeNode_abstract*>(parent.internalPointer());

  AATreeNode_abstract* childItem = parentItem->getChild(row);

  if (childItem)
    return createIndex(row, column, childItem);
  return QModelIndex();
}

QModelIndex AATreeModel::parent(const QModelIndex& index) const {
  qDebug() << "mama!";
  if (!index.isValid())
    return QModelIndex();

  AATreeNode_abstract* childItem =
      static_cast<AATreeNode_abstract*>(index.internalPointer());
  AATreeNode_abstract* parentItem = childItem->parent();

  if (parentItem == m_rootNode)
    return QModelIndex();

  return createIndex(parentItem->getIndex(), 0, parentItem);
}

int AATreeModel::rowCount(const QModelIndex& parent) const {
  AATreeNode_abstract* parentNode;
  if (!parent.isValid()) {
    parentNode = m_rootNode;
    qDebug() << "parentNode->children().size()";
    qDebug() << parentNode->children().size();
  } else {
    parentNode = static_cast<AATreeNode_abstract*>(parent.internalPointer());
    qDebug() << "index valid";
    qDebug() << parentNode->children().size();
  }
  return parentNode->children().size();
}

int AATreeModel::columnCount(const QModelIndex& parent) const {
  if (!parent.isValid())
    return 1;
}

QVariant AATreeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
    //    return QVariant(QString("HHH"));
    //    auto node = nodeFromIndex(index);
    auto node2 = static_cast<AATreeNode_abstract*>(index.internalPointer());
    return node2->name();
  }
  // FIXME: Implement me!
  return QVariant();
}

Qt::ItemFlags AATreeModel::flags(const QModelIndex& index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

bool AATreeModel::readFile(const QFile& file) {
  m_rootNode->readFromFile(file);
}
bool AATreeModel::writeFile(const QFile& file) {
  m_rootNode->writeToFile(file);
}

AATreeNode_abstract* AATreeModel::nodeFromIndex(const QModelIndex& index) {
  if (!index.isValid()) {
    return nullptr;
  }
  return static_cast<AATreeNode_abstract*>(index.internalPointer());
}
