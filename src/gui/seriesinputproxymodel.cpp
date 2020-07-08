#include "seriesinputproxymodel.h"

SeriesInputProxyModel::SeriesInputProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent) {}

void SeriesInputProxyModel::setSourceModel(QAbstractItemModel* sourceModel) {
  QSortFilterProxyModel::setSourceModel(sourceModel);
  m_sourceModel = qobject_cast<AATreeModel*>(sourceModel);
}

bool SeriesInputProxyModel::filterAcceptsRow(
    int source_row,
    const QModelIndex& source_parent) const {
  if (!m_sourceModel) {
    return true;
  }
  QModelIndex rowIndex;
  if (source_parent.isValid()) {
    // Not a root element
    rowIndex = source_parent;
  } else {
    // Likely a root element
    rowIndex = sourceModel()->index(source_row, 0, source_parent);
  }
  AATreeNode_abstract* node = m_sourceModel->nodeFromIndex(rowIndex);
  QString nodeName = node->name();
  if (nodeName != "sessions" && nodeName != "session") {
    return false;
  }

  return true;
}
