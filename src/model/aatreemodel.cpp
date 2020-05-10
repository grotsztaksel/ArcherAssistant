#include "aatreemodel.h"

AATreeModel::AATreeModel(QObject* parent) : QAbstractItemModel(parent) {
  m_rootNode = new AATreeNode_pugi(this, true);
}

AATreeModel::~AATreeModel() {
  m_rootNode->deleteLater();
}

QVariant AATreeModel::headerData(int section,
                                 Qt::Orientation orientation,
                                 int role) const {
  return QVariant();
}

QModelIndex AATreeModel::index(int row,
                               int column,
                               const QModelIndex& parent) const {
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
  if (!parent.isValid())
    return 0;

  // FIXME: Implement me!
}

int AATreeModel::columnCount(const QModelIndex& parent) const {
  if (!parent.isValid())
    return 1;
}

QVariant AATreeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
  }
  // FIXME: Implement me!
  return QVariant();
}

AATreeNode_abstract* AATreeModel::nodeFromIndex(const QModelIndex& index) {
  if (!index.isValid()) {
    return nullptr;
  }
  return static_cast<AATreeNode_abstract*>(index.internalPointer());
}
