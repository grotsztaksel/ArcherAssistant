#include "aatreemodel.h"

#include <QDebug>
AATreeModel::AATreeModel(QObject* parent) : QAbstractItemModel(parent) {
  m_rootNode = new AATreeNode_pugi();
}

AATreeModel::~AATreeModel() {
  m_rootNode->deleteLater();
}

QVariant AATreeModel::headerData(int section,
                                 Qt::Orientation orientation,
                                 int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return QVariant(QString("header"));
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

  AATreeNode_abstract* childItem = nodeFromIndex(index);
  AATreeNode_abstract* parentItem = childItem->parent();

  if (parentItem == m_rootNode)
    return QModelIndex();

  return createIndex(parentItem->getIndex(), 0, parentItem);
}

int AATreeModel::rowCount(const QModelIndex& parent) const {
  AATreeNode_abstract* parentNode;
  if (!parent.isValid()) {
    parentNode = m_rootNode;
  } else {
    parentNode = nodeFromIndex(parent);
  }
  return parentNode->children().size();
}

int AATreeModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return 1;
}

QVariant AATreeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
    auto node = nodeFromIndex(index);
    return node->name();
  }

  return QVariant();
}

Qt::ItemFlags AATreeModel::flags(const QModelIndex& index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QModelIndex AATreeModel::insertElement(QString name,
                                       QModelIndex parentIndex,
                                       int row) {
  int qtRow = row;
  if (row < 0) {
    qtRow = rowCount(parentIndex);
  }
  auto parentNode = nodeFromIndex(parentIndex);

  beginInsertRows(parentIndex, qtRow, qtRow);
  parentNode->addChild(name, row);
  endInsertRows();
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
