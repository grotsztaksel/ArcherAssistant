#include "pathviewproxymodel.h"

#include "aafilemanager.h"

#include <QDebug>
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *
 *
 *  Private implementation of a Proxy model
 *
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

pathViewModel::pathViewModel(QObject* parent)
    : QSortFilterProxyModel(parent),
      m_parentName(AAFileManager::getNodeName()) {}

bool pathViewModel::filterAcceptsRow(int source_row,
                                     const QModelIndex& source_parent) const {
  AATreeModel* model = qobject_cast<AATreeModel*>(sourceModel());
  if (!model)
    return false;

  if (model->nodeFromIndex(model->index(source_row, 0, source_parent))
          ->name() == m_parentName) {
    return true;
  }
  return (model->nodeFromIndex(source_parent)->name() == m_parentName);
}

// QModelIndex pathViewModel::parent(const QModelIndex& index) {
//  Q_UNUSED(index);
//  return QModelIndex();
//}

int pathViewModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return 1;
}

QVariant pathViewModel::data(const QModelIndex& index, int role) const {
  if (role == Qt::DisplayRole) {
    auto model = qobject_cast<AATreeModel*>(sourceModel());
    if (!model) {
      return QVariant();
    }
    AATreeNode_abstract* node = model->nodeFromIndex(mapToSource(index));

    if (node) {
      return node->attribute("dir");
    }
  }
  return QVariant();
}
