#ifndef AATREENODE_PUGI_H
#define AATREENODE_PUGI_H

#include <pugixml.hpp>
#include "aatreenode_abstract.h"
class AATreeNode_pugi : public AATreeNode_abstract {
  Q_OBJECT
 public:
  explicit AATreeNode_pugi(QObject* parent = nullptr);
  ~AATreeNode_pugi();

  //! Get type (name) of the element
  QString name();

  //! Get attribute of given type
  QVariant attribute(const QString name);

  //! check if the node has a given attribute
  bool hasAttribute(const QString name);

  //! set attribute of given name
  bool setAttribute(const QString name, const QVariant& value);

  //! clear attribute of given name
  bool removeAttribute(const QString name);
  //! Get list of all attributes
  QStringList attributes();

  //! Get list of direct children
  QList<AATreeNode_abstract*> children() const;

  //! Get the root node
  AATreeNode_abstract* root();

  void setDateTime(const QDateTime& dateTime);

 signals:

 protected:
  //! set the pugi pugi::xml_node object. Also, for each child detected in the
  //! pugi, create a representation of AATreeNode objects. This works
  //! recursively.
  void setXMLnode(pugi::xml_node node);

  //! helper function to quickly convert QString to char*
  const char* cstr(QString string);

 protected:
  QString m_name;
  pugi::xml_node m_xml_node;
  AATreeNode_pugi* m_parent = nullptr;
  QList<AATreeNode_pugi*> m_children;
  QDateTime m_dateTime;
};

#endif  // AATREENODE_PUGI_H
