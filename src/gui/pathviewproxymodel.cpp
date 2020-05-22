#include "pathviewproxymodel.h"

#include "aafilemanager.h"

#include <QColor>
#include <QDebug>
#include <QDir>
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
    auto node = getSourceNode(index);
    if (node) {
      return node->attribute("dir");
    }
  } else if (role == Qt::ForegroundRole) {
    auto node = getSourceNode(index);
    if (node) {
      QDir dir(node->attribute("dir").toString());
      if (!dir.exists()) {
        return QColor(Qt::gray);
      }
    }
  }
  return QVariant();
}

AATreeNode_abstract* pathViewModel::getSourceNode(
    const QModelIndex& index) const {
  QModelIndex idx;
  if (index.model() == this) {
    idx = mapToSource(index);
  } else if (index.model() == sourceModel()) {
    idx = index;
  } else {
    return nullptr;
  }
  AATreeModel* model = qobject_cast<AATreeModel*>(sourceModel());
  if (!model) {
    return nullptr;
  }
  AATreeNode_abstract* node = model->nodeFromIndex(mapToSource(index));
  return node;
}
