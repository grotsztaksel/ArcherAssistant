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
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (showItemsInFirstColumn() && section == 0) {
      return QVariant(m_elementHeader);
    }
    if (m_headers.empty()) {
      return QVariant();
    } else {
      return QVariant(m_headers.at(section - int(showItemsInFirstColumn())));
    }
  }
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
  AATreeNode_abstract* parentNode = nodeFromIndex(parent);
  return parentNode->children().size();
}

int AATreeModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  int count = m_headers.size();
  if (count == 0) {
    return 1;
  } else {
    return count;
  }
}

QVariant AATreeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
    AATreeNode_abstract* node = nodeFromIndex(index);
    if (showItemsInFirstColumn() && index.column() == 0) {
      return node->name();
    }

    if (m_headers.empty()) {
      return node->name();
    } else {
      QString attrName =
          m_headers.at(index.column() - int(showItemsInFirstColumn()));
      return node->attribute(attrName);
    }
  }

  return QVariant();
}

Qt::ItemFlags AATreeModel::flags(const QModelIndex& index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

bool AATreeModel::removeRows(int row, int count, const QModelIndex& parent) {
  AATreeNode_abstract* parentNode = nodeFromIndex(parent);
  bool ok = true;
  beginRemoveRows(parent, row, row + count - 1);
  for (int i = row; i < row + count; i++) {
    ok &= parentNode->removeChild(row);
  }
  endRemoveRows();
  return ok;
}

bool AATreeModel::moveRows(const QModelIndex& sourceParent,
                           int sourceRow,
                           int count,
                           const QModelIndex& destinationParent,
                           int destinationChild) {
  AATreeNode_abstract* parentNode = nodeFromIndex(sourceParent);
  AATreeNode_abstract* destinationParentNode = nodeFromIndex(destinationParent);

  int sourceLast = sourceRow + count - 1;
  qDebug() << sourceRow << count << sourceLast << destinationChild
           << destinationChild + count - 1;

  int deleteFrom = sourceRow;

  int increment = 0;
  if (sourceParent == destinationParent) {
    if (sourceRow > destinationChild) {
      // Moving the rows up
      deleteFrom = sourceRow + count;
      increment = 1;
    } else if (sourceRow == destinationChild) {
      // moving to the same location. Nothing to do.
      return true;
    } else if (sourceRow < destinationChild) {
      // Moving the nodes down
      if (sourceLast + 1 <= destinationChild) {
        destinationChild = sourceLast + 2;
      }
    }
  }

  if (!beginMoveRows(sourceParent, sourceRow, sourceLast, destinationParent,
                     destinationChild))
    return false;
  for (int i = 0; i < count; i++) {
    AATreeNode_abstract* moved_node =
        parentNode->getChild(i + sourceRow + increment * i);
    destinationParentNode->insertChild(moved_node, i + destinationChild);
  }
  bool ok = true;

  for (int i = 0; i < count; i++) {
    ok &= parentNode->removeChild(deleteFrom);
  }
  endMoveRows();
  return ok;
}

QModelIndex AATreeModel::insertElement(QString name,
                                       QModelIndex parentIndex,
                                       int row) {
  if (row < 0) {
    row = rowCount(parentIndex);
  }
  AATreeNode_abstract* parentNode = nodeFromIndex(parentIndex);
  beginInsertRows(parentIndex, row, row);
  parentNode->addChild(name, row);
  endInsertRows();
}

bool AATreeModel::readFile(const QFile& file) {
  m_rootNode->readFromFile(file);
}
bool AATreeModel::writeFile(const QFile& file) {
  m_rootNode->writeToFile(file);
}

void AATreeModel::setHeaders(const QStringList& headers) {
  m_headers = headers;
}

QString AATreeModel::elementHeader() const {
  return m_elementHeader;
}

void AATreeModel::setElementHeader(const QString& elementHeader) {
  m_elementHeader = elementHeader;
}

AATreeNode_abstract* AATreeModel::nodeFromIndex(
    const QModelIndex& index) const {
  if (!index.isValid()) {
    return m_rootNode;
  }
  return static_cast<AATreeNode_abstract*>(index.internalPointer());
}

bool AATreeModel::showItemsInFirstColumn() const {
  return !m_elementHeader.isEmpty();
}
