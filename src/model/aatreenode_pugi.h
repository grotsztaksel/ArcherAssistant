#ifndef AATREENODE_PUGI_H
#define AATREENODE_PUGI_H

#include <pugixml.hpp>
#include "aatreenode_abstract.h"
//! Implementation of AATreeNode using pugixml as the data handling logic
class AATreeNode_pugi : public AATreeNode_abstract {
  Q_OBJECT
 public:
  explicit AATreeNode_pugi(QObject* parent = nullptr, bool isRoot = false);
  ~AATreeNode_pugi();

  /*------------------------------*
   *                              *
   *      BASIC METHODS           *
   *                              *
   *------------------------------*/

  //! Get type (name) of the element
  //!
  QString name() override;

  //! Identify the index at which this row resides in its parent node
  //!
  int getIndex() override;

  //! Reset the currently held data and read from a file. Works only on root
  //! node
  //!
  bool readFromFile(const QFile& file) override;

  //! Write the content of the current structure to file.  Works only on root
  //! node
  //!
  bool writeToFile(const QFile& file) override;

  //  //! Get the root node
  //  //!
  //  AATreeNode_abstract* root() override;

  //! Get the node's parent node
  //!
  AATreeNode_abstract* parent() override;

  /*------------------------------*
   *                              *
   *      ATTRIBUTE METHODS       *
   *                              *
   *------------------------------*/

  //! Get list of all attributes
  //!
  QStringList attributes() override;

  //! Get attribute of given type
  //!
  QVariant attribute(const QString name) override;

  //! check if the node has a given attribute
  //!
  bool hasAttribute(const QString name) override;

  //! set attribute of given name
  //!
  bool setAttribute(const QString name, const int& value) override;
  bool setAttribute(const QString name, const QString& value) override;
  bool setAttribute(const QString name, const double& value) override;
  bool setAttribute(const QString name, const bool& value) override;

  //! clear attribute of given name
  //!
  bool removeAttribute(const QString name) override;

  /*------------------------------*
   *                              *
   *      CHILD NODE METHODS      *
   *                              *
   *------------------------------*/

  //! Get list of direct children
  //!
  QList<AATreeNode_abstract*> children() const override;

  //! Get list of children of given name
  //!
  QList<AATreeNode_abstract*> children(const QString& name) const override;

  //! Get the child node at given index (starting from zero)
  //!
  AATreeNode_abstract* getChild(int index) const override;

  //! Create child of given name then insert it before index-th node. If no
  //! index provided, or if the index exceeds the number of children, insert at
  //! the end
  //!
  AATreeNode_abstract* addChild(const QString& name,
                                const int index = -1) override;

  //! insert already created child object before index-th node. If no index
  //! provided, or if the index exceeds the number of children, insert at the
  //! end
  //!
  AATreeNode_abstract* insertChild(AATreeNode_abstract* child,
                                   const int index = -1) override;

  //  //! Remove index-th child of given name. If no index is provided, remove
  //  last
  //  //! child of this name
  //  //!
  //  AATreeNode_abstract* removeChild(const QString& name,
  //                                   const int index = -1) override;

  //  //! Remove index-th child, regardless of its name. If index not provided,
  //  //! remove last child
  //  //!
  //  AATreeNode_abstract* removeChild(const int index = -1) override;

 signals:

 protected:
  //! protected overloaded version of insertChild. This is required to
  //! enable using insertChild in implementation of the addChild (see both
  //! implementations)
  //!
  AATreeNode_abstract* insertChild(AATreeNode_abstract* child,
                                   const int index = -1,
                                   const QString& name = QString());

  //! set the pugi pugi::xml_node object. Also, for each child detected in the
  //! pugi, create a representation of AATreeNode objects. This works
  //! recursively.
  //!
  void setXMLnode(pugi::xml_node node);

  //! helper function to quickly convert QString to char*
  //!
  static const char* cstr(QString string);

  //! Helper function to access the node, optimizing the cost of getting the
  //! node at given index. It uses the next/previous_child xml_node functions
  //! @warning: This method does not check whether the index is within correct
  //! range.
  //!
  pugi::xml_node xml_nodeAtIndex(const int i);

  //! Helper function returning the number of children.to update
  //! m_number_of_children (pugi itself doesn't offer such functionality)
  //!
  int numberOfChildren();

 protected:
  QString m_name;
  pugi::xml_node m_xml_node;
  AATreeNode_pugi* m_parent = nullptr;
  QList<AATreeNode_pugi*> m_children;

  int m_last_searched_xml_node_index = 0;
  pugi::xml_node m_last_searched_xml_node;

  //! If the node is a root node, the xml document should be created.
  pugi::xml_document* m_doc = nullptr;
};

#endif  // AATREENODE_PUGI_H
