#ifndef AATREENODE_PUGI_H
#define AATREENODE_PUGI_H

#include <pugixml.hpp>
#include "aatreenode_abstract.h"
//! Implementation of AATreeNode using pugixml as the data handling logic
class AATreeNode_pugi : public AATreeNode_abstract {
  Q_OBJECT
 public:
  explicit AATreeNode_pugi(QObject* parent = nullptr);
  ~AATreeNode_pugi();

  /*------------------------------*
   *                              *
   *      BASIC METHODS           *
   *                              *
   *------------------------------*/

  //! Get type (name) of the element
  QString name() override;

  //! Get the root node
  AATreeNode_pugi* root() override;

  //! Get the node's parent node
  AATreeNode_pugi* parent() override;

  /*------------------------------*
   *                              *
   *      ATTRIBUTE METHODS       *
   *                              *
   *------------------------------*/

  //! Get list of all attributes
  QStringList attributes() override;

  //! Get attribute of given type
  QVariant attribute(const QString name) override;

  //! check if the node has a given attribute
  bool hasAttribute(const QString name) override;

  //! set attribute of given name
  bool setAttribute(const QString name, const int& value) override;
  bool setAttribute(const QString name, const QString& value) override;
  bool setAttribute(const QString name, const double& value) override;
  bool setAttribute(const QString name, const bool& value) override;

  //! clear attribute of given name
  bool removeAttribute(const QString name) override;

  /*------------------------------*
   *                              *
   *      CHILD NODE METHODS      *
   *                              *
   *------------------------------*/

  //! Get list of direct children
  QList<AATreeNode_pugi*> children() const override;

  //! Get list of children of given name
  QList<AATreeNode_pugi*> children(QString name) const override;
  //! Get the child node at given index (starting from zero)
  QList<AATreeNode_pugi*> getChild(int index) const override;

  //! Create child of given name then insert it before index-th node. If no
  //! index provided, or if the index exceeds the number of children, insert at
  //! the end
  AATreeNode_pugi* addChild(QString name, int index = -1) override;

  //! insert already created child object before index-th node. If no index
  //! provided, or if the index exceeds the number of children, insert at the
  //! end
  AATreeNode_pugi* insertChild(AATreeNode_pugi* child, int index = -1) override;

  //! Remove index-th child of given name. If no index is provided, remove last
  //! child of this name
  AATreeNode_pugi* removeChild(QString name, int index = -1) override;

  //! Remove index-th child, regardless of its name. If index not provided,
  //! remove last child
  AATreeNode_pugi* removeChild(int index = -1) override;

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
};
}
;

#endif  // AATREENODE_PUGI_H
