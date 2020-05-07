#include "aatreemodel.h"

AATreeModel::AATreeModel(QObject* parent) : QAbstractItemModel(parent) {}

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
  AATreeNode* node;
  return createIndex(row, column, node);
}

QModelIndex AATreeModel::parent(const QModelIndex& index) const {
  // FIXME: Implement me!
}

int AATreeModel::rowCount(const QModelIndex& parent) const {
  if (!parent.isValid())
    return 0;

  // FIXME: Implement me!
}

int AATreeModel::columnCount(const QModelIndex& parent) const {
  if (!parent.isValid())
    return 0;

  // FIXME: Implement me!
}

QVariant AATreeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();

  // FIXME: Implement me!
  return QVariant();
}
