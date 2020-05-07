#include "aatreenode_pugi.h"

AATreeNode_pugi::AATreeNode_pugi(QObject* parent)
    : AATreeNode_abstract(parent) {}

AATreeNode_pugi::~AATreeNode_pugi() {
  // Clear the pugi structure
  m_xml_node.parent().remove_child(m_xml_node);

  // delete the QObjects
  for (AATreeNode_pugi* child : m_children) {
    child->deleteLater();
  }
}

QString AATreeNode_pugi::name() {
  return QString(m_xml_node.name());
}

QVariant AATreeNode_pugi::attribute(const QString name) {
  auto attrib = m_xml_node.attribute(cstr(name));
  if (!attrib)
    return QVariant();
  return attrib.value();
}

bool AATreeNode_pugi::hasAttribute(const QString name) {
  return m_xml_node.attribute(cstr(name));
}

bool AATreeNode_pugi::setAttribute(const QString name, const int& value) {
  return m_xml_node.attribute(cstr(name)).set_value(value);
}
bool AATreeNode_pugi::setAttribute(const QString name, const QString& value) {
  return m_xml_node.attribute(cstr(name)).set_value(cstr(value));
}
bool AATreeNode_pugi::setAttribute(const QString name, const double& value) {
  return m_xml_node.attribute(cstr(name)).set_value(value);
}
bool AATreeNode_pugi::setAttribute(const QString name, const bool& value) {
  return m_xml_node.attribute(cstr(name)).set_value(value);
}

bool AATreeNode_pugi::removeAttribute(const QString name) {
  return m_xml_node.remove_attribute(cstr(name));
}

QStringList AATreeNode_pugi::attributes() {
  QStringList attributes;
  for (auto attrib : m_xml_node.attributes()) {
    if (attrib)
      attributes << QString(attrib.name());
  }
  return attributes;
}

AATreeNode_abstract* AATreeNode_pugi::root() {
  auto root = m_xml_node.root();
  AATreeNode_pugi* rootnode = new AATreeNode_pugi();
  rootnode->setXMLnode(root);
  return rootnode;
}

QList<AATreeNode_abstract*> AATreeNode_pugi::children() const {
  QList<AATreeNode_abstract*> children;

  for (pugi::xml_node node : m_xml_node.children()) {
    AATreeNode_pugi* child = new AATreeNode_pugi();
    child->setXMLnode(node);
    children.append(child);
  }
  return children;
}
// ------------- protected methods -----------------
void AATreeNode_pugi::setXMLnode(pugi::xml_node node) {
  m_xml_node = node;
}

const char* AATreeNode_pugi::cstr(QString string) {
  return string.toStdString().c_str();
}
