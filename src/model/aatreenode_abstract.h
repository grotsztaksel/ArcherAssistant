#ifndef AATREENODE_ABSTRACT_H
#define AATREENODE_ABSTRACT_H

#include <QDateTime>
#include <QList>
#include <QObject>
//! An abstract, pure virtual tree node class. The AATreeModel should use
//! derived classes with the actual implementation of the data handling. The
//! AATreeModel should be completely agnostic to what technology is used to
//! handle the data (e.g. some XML library, HDF or even just custom plain text
//! format).
//! This architecture has been introduced in order to separate the data specific
//! logic from the general logic used by the model. Ideally, switching the logic
//! should be as simple as selecting another name of the tree node class in the
//! AATreeModel
//! Therefore, the derived classes should not expose any new public objects or
//! methods
class AATreeNode_abstract : public QObject {
  Q_OBJECT
 public:
  explicit AATreeNode_abstract(QObject* parent = nullptr);

  //! Get type (name) of the element
  virtual QString name() = 0;

  //! Get attribute of given type
  virtual QVariant attribute(const QString name) = 0;

  //! check if the node has a given attribute
  virtual bool hasAttribute(const QString name) = 0;

  //! set attribute of given name
  virtual bool setAttribute(const QString name, const int& value) = 0;
  virtual bool setAttribute(const QString name, const QString& value) = 0;
  virtual bool setAttribute(const QString name, const double& value) = 0;
  virtual bool setAttribute(const QString name, const bool& value) = 0;

  //! clear attribute of given name
  virtual bool removeAttribute(const QString name) = 0;
  //! Get list of all attributes
  virtual QStringList attributes() = 0;

  //! Get list of direct children
  virtual QList<AATreeNode_abstract*> children() const = 0;

  //! Add child of given name. If index provided, will insert before the
  //! index-th node. Otherwise will append to the end
  virtual AATreeNode_abstract* addChild(QString name, int index = -1) = 0;

  //! insert already created child object at at index. If no index provided,
  //! insert at the end
  virtual AATreeNode_abstract* insertChild(AATreeNode_abstract* child,
                                           int index = -1) = 0;

  //! Remove index-th child of given name. If no index is provided, remove first
  //! child of this name
  virtual AATreeNode_abstract* removeChild(QString name, int index = -1) = 0;

  //! Remove index-th child, regardless of its name. If index not provided,
  //! remove first child
  virtual AATreeNode_abstract* removeChild(int index = -1) = 0;

  //! Get the root node
  virtual AATreeNode_abstract* root() = 0;
};

#endif  // AATREENODE_ABSTRACT_H
