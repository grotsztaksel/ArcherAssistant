#include "aatreenode.h"

AATreeNode::AATreeNode(QString name, AATreeNode* xmlParent, QObject* parent)
    : QObject(parent), m_name{name}, m_parent{xmlParent} {}

AATreeNode::~AATreeNode() {
  // Clear the pugi structure
  m_xml_node.parent().remove_child(m_xml_node);

  // delete the QObjects
  for (AATreeNode* child : m_children) {
    child->deleteLater();
  }
}

QDate AATreeNode::date() {
  return m_dateTime.date();
}

QTime AATreeNode::time() {
  return m_dateTime.time();
}

QDateTime AATreeNode::dateTime() const {
  return m_dateTime;
}

QString AATreeNode::name() {
  return QString(m_xml_node.name());
}

QVariant AATreeNode::attribute(const QString name) {
  auto attrib = m_xml_node.attribute(cstr(name));
  if (!attrib)
    return QVariant();
  return attrib.value();
}

bool AATreeNode::hasAttribute(const QString name) {
  return m_xml_node.attribute(cstr(name));
}

QStringList AATreeNode::attributes() {
  QStringList attributes;
  for (auto attrib : m_xml_node.attributes()) {
    if (attrib)
      attributes << QString(attrib.name());
  }
  return attributes;
}

AATreeNode* AATreeNode::root() {}

void AATreeNode::setDateTime(const QDateTime& dateTime) {
  m_dateTime = dateTime;
}

void AATreeNode::setXMLnode(pugi::xml_node node) {
  m_xml_node = node;
  m_children.clear();
  for (pugi::xml_node node : m_xml_node.children()) {
    AATreeNode* child = new AATreeNode(QString(node.name()));

    m_children.append(child);
    child->setXMLnode(node);
  }
}

const char* AATreeNode::cstr(QString string) {
  return string.toStdString().c_str();
}

QList<AATreeNode*> AATreeNode::children() const {
  return m_children;
}
