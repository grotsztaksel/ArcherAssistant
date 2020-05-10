#include "aatreenode_pugi.h"

#include <QDebug>
using namespace pugi;
AATreeNode_pugi::AATreeNode_pugi(QObject* parent, bool isRoot)
    : AATreeNode_abstract(parent, isRoot) {
  if (m_isRoot) {
    m_doc = new xml_document();
    qDebug() << "New Node" << isRoot << m_isRoot
             << m_doc->document_element().name();
    setXMLnode(m_doc->document_element());
  } else {
    qDebug() << "New subnode, "
             << qobject_cast<AATreeNode_pugi*>(parent)->name();
  }
}

AATreeNode_pugi::~AATreeNode_pugi() {
  // Clear the pugi structure
  if (m_isRoot && m_doc) {
    // if it is a root, it should have a document. Deleting it should clear all
    // its xml_node children.
    delete m_doc;
  } else {
    // it is not root. Need to access myself from parent level, because there is
    // no way to delete the xml_node from self level
    m_xml_node.parent().remove_child(m_xml_node);
  }

  // delete the QObjects
  for (AATreeNode_pugi* child : m_children) {
    child->deleteLater();
  }
}

QString AATreeNode_pugi::name() {
  return QString(m_xml_node.name());
}

int AATreeNode_pugi::getIndex() {
  int i = 0;
  auto previous = m_xml_node.previous_sibling();
  while (previous) {
    i++;
    previous = m_xml_node.previous_sibling();
  }
  return i;
}

bool AATreeNode_pugi::readFromFile(const QFile& file) {
  qDebug() << "ReadFromFile" << m_isRoot << file.exists() << file.fileName();
  if (!(m_isRoot && file.exists()))
    return false;

  m_doc->reset();
  auto name = cstr(file.fileName());
  m_doc->load_file(name);
  qDebug() << "doc after read" << m_isRoot << m_doc->document_element().name();
  setXMLnode(m_doc->document_element());
  return m_xml_node;
}

bool AATreeNode_pugi::writeToFile(const QFile& file) {
  qDebug() << "They want me to save. Am I a root?" << m_isRoot;
  if (!(m_isRoot))
    return false;
  auto name = cstr(file.fileName());
  m_doc->save_file(name, "  ");
  qDebug() << "saved file and still alive";
  return true;
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

// AATreeNode_abstract* AATreeNode_pugi::root() {
//  auto root = m_xml_node.root();
//  AATreeNode_pugi* rootnode = new AATreeNode_pugi(this);
//  rootnode->setXMLnode(root);
//  return rootnode;
//}

AATreeNode_abstract* AATreeNode_pugi::parent() {
  return m_parent;
}

QList<AATreeNode_abstract*> AATreeNode_pugi::children() const {
  QList<AATreeNode_abstract*> children;

  for (AATreeNode_abstract* child : m_children) {
    AATreeNode_abstract* child_ptr_copy = child;
    children.append(child_ptr_copy);
  }
  return children;
}

QList<AATreeNode_abstract*> AATreeNode_pugi::children(
    const QString& name) const {
  QList<AATreeNode_abstract*> children;
  for (AATreeNode_abstract* child : m_children) {
    if (child->name() == name) {
      AATreeNode_abstract* child_ptr_copy = child;
      children.append(child_ptr_copy);
    }
  }
  return children;
}

AATreeNode_abstract* AATreeNode_pugi::getChild(int index) const {
  if (index < m_children.size() && index > -1)
    return m_children.at(index);
  return nullptr;
}

AATreeNode_abstract* AATreeNode_pugi::addChild(const QString& name, int index) {
  AATreeNode_pugi* newNode = new AATreeNode_pugi(this);
  return insertChild(newNode, index, name);
}

AATreeNode_abstract* AATreeNode_pugi::insertChild(AATreeNode_abstract* child,
                                                  int index) {
  QString name;
  return insertChild(child, index, name);
}

AATreeNode_abstract* AATreeNode_pugi::insertChild(AATreeNode_abstract* child,
                                                  int index,
                                                  const QString& name) {
  xml_node newXMLNode;
  if (index == -1) {
    m_xml_node.append_child(cstr(name));
  } else {
    xml_node myOlderBrother = xml_nodeAtIndex(index);
    m_xml_node.insert_child_before(cstr(name), myOlderBrother);
  }
  AATreeNode_pugi* pugiChild = qobject_cast<AATreeNode_pugi*>(child);
  if (child)
    pugiChild->setXMLnode(newXMLNode);
  return pugiChild;
}

// ------------- protected methods -----------------
void AATreeNode_pugi::setXMLnode(pugi::xml_node node) {
  m_xml_node = node;
  qDebug() << "setXMLnode" << node.name();
  m_children.clear();
  for (xml_node child : node.children()) {
    AATreeNode_pugi* c = new AATreeNode_pugi(this);
    c->setXMLnode(child);
    m_children.append(c);
  }
}

const char* AATreeNode_pugi::cstr(QString string) {
  return string.toStdString().c_str();
}

xml_node AATreeNode_pugi::xml_nodeAtIndex(int i) {
  // try addressing the most probable cases:
  // - accessing the next node,
  // - accessing the first node,
  // - accessing the same node again,
  // - accessing the previous node
  if (i == m_last_searched_xml_node_index + 1) {
    // quite an expected case - iterating nodes one after another
    m_last_searched_xml_node = m_last_searched_xml_node.next_sibling();
    m_last_searched_xml_node_index++;
    return m_last_searched_xml_node;
  } else if (i == 0) {
    m_last_searched_xml_node = m_xml_node.first_child();
    m_last_searched_xml_node_index = 0;
    return m_last_searched_xml_node;
  } else if (i == m_last_searched_xml_node_index) {
    return m_last_searched_xml_node;
  } else if (i == m_last_searched_xml_node_index - 1) {
    // quite an expected case - iterating nodes one after another, backwards
    m_last_searched_xml_node = m_last_searched_xml_node.previous_sibling();
    m_last_searched_xml_node_index--;
    return m_last_searched_xml_node;
  }

  //
  //
  //
  // if we didn't get result by now, it pays to do more math
  //
  int N = numberOfChildren() - 1;

  if (i == N) {
    m_last_searched_xml_node = m_xml_node.last_child();
    m_last_searched_xml_node_index = N;
    return m_last_searched_xml_node;
  } else if (m_last_searched_xml_node_index - i < i) {
    // i closer to 0 => iterate forward from 0
    xml_node node = m_xml_node.first_child();
    int j = 0;
    while (j != i) {
      node = node.next_sibling();
      j++;
    }
    m_last_searched_xml_node = node;
    m_last_searched_xml_node_index = j;
  } else if (m_last_searched_xml_node_index - i > i) {
    // i closer to last used, and smaller => iterate backwards from last used
    xml_node node = m_last_searched_xml_node;
    int j = m_last_searched_xml_node_index;
    while (j != i) {
      node = node.previous_sibling();
      j--;
    }
    m_last_searched_xml_node = node;
    m_last_searched_xml_node_index = j;

  } else if (N - i < i - m_last_searched_xml_node_index) {
    // i closer to N => iterate backwards from N
    xml_node node = m_xml_node.last_child();
    int j = N;
    while (j != i) {
      node = node.previous_sibling();
      j--;
    }
    m_last_searched_xml_node = node;
    m_last_searched_xml_node_index = j;

  } else if (N - i < i - m_last_searched_xml_node_index) {
    // i closer to last used, and larger => iterate forward from last used
    xml_node node = m_last_searched_xml_node;
    int j = m_last_searched_xml_node_index;
    while (j != i) {
      node = node.next_sibling();
      j++;
    }
    m_last_searched_xml_node = node;
    m_last_searched_xml_node_index = j;
  }
  return m_last_searched_xml_node;
}

int AATreeNode_pugi::numberOfChildren() {
  m_children.size();
}
