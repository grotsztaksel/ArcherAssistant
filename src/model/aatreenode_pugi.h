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
  QString name() override;

  //! Get attribute of given type
  QVariant attribute(const QString name) override;

  //! check if the node has a given attribute
  bool hasAttribute(const QString name) override;

  //! set attribute of given name
  virtual bool setAttribute(const QString name, const int& value) override;
  virtual bool setAttribute(const QString name, const QString& value) override;
  virtual bool setAttribute(const QString name, const double& value) override;
  virtual bool setAttribute(const QString name, const bool& value) override;

  //! clear attribute of given name
  bool removeAttribute(const QString name) override;
  //! Get list of all attributes
  QStringList attributes() override;

  //! Get list of direct children
  QList<AATreeNode_abstract*> children() const override;

  //! Get the root node
  AATreeNode_abstract* root() override;

  void setDateTime(const QDateTime& dateTime) override;

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
