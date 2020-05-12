#include "aatreenode_abstract.h"

AATreeNode_abstract::AATreeNode_abstract(QObject* parent) : QObject(parent) {}

AATreeNode_abstract* AATreeNode_abstract::root() {
  auto node = this;
  while (node->parent()) {
    node = node->parent();
  }
  return node;
}
