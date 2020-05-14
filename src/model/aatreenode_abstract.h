#ifndef AATREENODE_ABSTRACT_H
#define AATREENODE_ABSTRACT_H

#include <QDateTime>
#include <QFile>
#include <QObject>
#include <QVariant>
#include <QVector>
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
  //! The constructor
  //!
  explicit AATreeNode_abstract(QObject* parent = nullptr);

  /*------------------------------*
   *                              *
   *      BASIC METHODS           *
   *                              *
   *------------------------------*/

  //! Get type (name) of the element
  //!
  virtual QString name() = 0;

  //! Identify the index at which this row resides in its parent node
  //!
  virtual int getIndex() = 0;

  //! Reset the currently held data and read from a file. Works only on root
  //! node
  //!
  virtual bool readFromFile(const QFile& file) = 0;

  //! Write the content of the current structure to file.  Works only on root
  //! node
  //!
  virtual bool writeToFile(const QFile& file) = 0;

  //! Get the root node
  //!
  virtual AATreeNode_abstract* root();

  //! Get the node's parent node
  //!
  virtual AATreeNode_abstract* parent() = 0;

  /*------------------------------*
   *                              *
   *      ATTRIBUTE METHODS       *
   *                              *
   *------------------------------*/

  //! Get list of all attributes
  //!
  virtual QStringList attributes() = 0;

  //! Get attribute of given type
  //!
  virtual QVariant attribute(const QString name) = 0;

  //! check if the node has a given attribute
  //!
  virtual bool hasAttribute(const QString name) = 0;

  //! set attribute of given name
  //!
  virtual bool setAttribute(const QString name, const int& value) = 0;
  virtual bool setAttribute(const QString name, const QString& value) = 0;
  virtual bool setAttribute(const QString name, const double& value) = 0;
  virtual bool setAttribute(const QString name, const bool& value) = 0;

  //! clear attribute of given name
  //!
  virtual bool removeAttribute(const QString name) = 0;

  /*------------------------------*
   *                              *
   *      CHILD NODE METHODS      *
   *                              *
   *------------------------------*/

  //! Get list of direct children
  //!
  virtual QVector<AATreeNode_abstract*> children() const = 0;

  //! Get list of children of given name
  //!
  virtual QVector<AATreeNode_abstract*> children(const QString& name) const = 0;

  //! Get the child node at given index (starting from zero)
  //!
  virtual AATreeNode_abstract* getChild(const int index) const = 0;

  //! Get the index-th named child node (starting from zero)
  //!
  virtual AATreeNode_abstract* getChild(QString name, int index = 0) const = 0;

  //! Create child of given name then insert it before index-th node. If no
  //! index provided, or if the index exceeds the number of children, insert at
  //! the end
  virtual AATreeNode_abstract* addChild(const QString& name,
                                        int index = -1) = 0;

  //! insert already created child object before index-th node. If no index
  //! provided, or if the index exceeds the number of children, insert at the
  //! end
  virtual AATreeNode_abstract* insertChild(AATreeNode_abstract* child,
                                           int index = -1) = 0;

  //! Remove index-th child of given name. If no index is provided, remove
  //  last
  //! child of this name
  virtual bool removeChild(const QString& name, const int index = -1) = 0;

  //  //! Remove index-th child, regardless of its name. If index not provided,
  //  //! remove last child
  virtual bool removeChild(const int index = -1) = 0;
  //
};

#endif  // AATREENODE_ABSTRACT_H
