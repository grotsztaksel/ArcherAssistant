#include "aatreenode_abstract.h"

AATreeNode_abstract::AATreeNode_abstract(QObject* parent) : QObject(parent) {}

AATreeNode_abstract* AATreeNode_abstract::root() {
  auto node = this;
  while (node->parent()) {
    node = node->parent();
  }
  return node;
}

QVariant AATreeNode_abstract::inheritedAttribute(const QString name,
                                                 int checkParents) {
  auto node = this;
  while (node) {
    if (node->hasAttribute(name)) {
      return node->attribute(name);
    }
    node = node->parent();
    if (checkParents == 0) {  // if checkParents was -1, then it will never be
                              // 0; Hence, will be looking up to the root node
      break;
    }
    checkParents--;
  }
  return QVariant();
}

QVariant AATreeNode_abstract::inheritedAttribute(const QString name,
                                                 QString oldestAncestorName) {
  auto node = this;
  while (node) {
    if (node->hasAttribute(name)) {
      return node->attribute(name);
    }
    if (node->name() == oldestAncestorName) {
      break;
    }
    node = node->parent();
  }
  return QVariant();
}

int AATreeNode_abstract::hasInheritedAttribute(const QString name,
                                               int checkParents) {
  int parentLevel = 0;
  auto node = this;
  while (node && (parentLevel <= checkParents || checkParents == -1)) {
    if (node->hasAttribute(name)) {
      return parentLevel;
    }
    parentLevel++;
    node = node->parent();
  }
  return -1;
}

QString AATreeNode_abstract::hasInheritedAttribute(const QString name,
                                                   QString oldestAncestorName) {
  auto node = this;
  while (node) {
    if (node->hasAttribute(name)) {
      return node->name();
    }
    if (node->name() == oldestAncestorName) {
      break;
    }
    node = node->parent();
  }
  return QString();
}
