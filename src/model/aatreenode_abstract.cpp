#include "aatreenode_abstract.h"

AATreeNode_abstract::AATreeNode_abstract(QObject* parent, bool isRoot)
    : QObject(parent), m_isRoot(isRoot) {}

AATreeNode_abstract* AATreeNode_abstract::root() {
  auto node = this;
  while (!node->m_isRoot) {
    node = node->parent();
  }
  return node;
}
