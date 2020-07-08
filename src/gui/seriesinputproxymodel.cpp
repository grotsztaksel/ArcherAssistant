#include "seriesinputproxymodel.h"

#include <QColor>

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

QVariant SeriesInputProxyModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) {
    return QSortFilterProxyModel::data(index, role);
  }
  QModelIndex srcIndex = mapToSource(index);
  auto node = m_sourceModel->nodeFromIndex(srcIndex);

  if (role == Qt::BackgroundRole) {
    if (node->isNew) {
      return QColor(Qt::green).lighter(188);
    }

  } else if (role == Qt::DisplayRole) {
    if (node->hasAttribute("DateTime")) {
      auto date = node->attribute("DateTime").toString();
      auto data = QSortFilterProxyModel::data(index, role).toString();
      return QVariant(QString("%1 (%2)").arg(data).arg(date));
    }
  }

  return QSortFilterProxyModel::data(index, role);
}
