#ifndef AATREEMODEL_H
#define AATREEMODEL_H

#include <QAbstractItemModel>

#include "aatreenode_pugi.h"

class AATreeModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit AATreeModel(QObject* parent = nullptr);
  ~AATreeModel();
  /*--------------------------------------*
   *                                      *
   *     QAbstractItemModel overrides     *
   *                                      *
   *--------------------------------------*/

  //! Returns the data for the given role and section in the header with the
  //! specified orientation.
  //!
  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  //! Returns the index of the item in the model specified by the given row,
  //! column and parent index.
  //!
  QModelIndex index(int row,
                    int column,
                    const QModelIndex& parent = QModelIndex()) const override;

  //! Returns the parent of the model item with the given index. If the item has
  //! no parent, an invalid QModelIndex is returned.
  //!
  QModelIndex parent(const QModelIndex& index) const override;

  //! Returns the number of rows under the given parent. When the parent is
  //! valid it means that rowCount is returning the number of children of
  //! parent.
  //!
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  //! Returns the number of columns for the children of the given parent.
  //!
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

  //! Returns the data stored under the given role for the item referred to by
  //! the index.
  //! If the model's @m_headers is empty, will return the node's name.
  //! Otherwise, it will return value of element's attribute, whose name is in
  //! the header of a given column. If the element does not have this attribute,
  //! will return empty QVariant. If there are attributes that have not their
  //! respective columns, the model will not query for them
  //!
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

  //! Returns the item flags for the given index.
  //!
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  //! Removes count rows starting with the given row under parent parent from
  //! the model. Returns true if the rows were successfully removed; otherwise
  //! returns false.
  //!
  bool removeRows(int row,
                  int count,
                  const QModelIndex& parent = QModelIndex()) override;

  //! Moves count rows starting with the given sourceRow under parent
  //! sourceParent to row destinationChild under parent destinationParent.
  //! Returns true if the rows were successfully moved; otherwise returns false.
  //!
  bool moveRows(const QModelIndex& sourceParent,
                int sourceRow,
                int count,
                const QModelIndex& destinationParent,
                int destinationChild);

  /*--------------------------------------*
   *                                      *
   *     Other functionality              *
   *                                      *
   *--------------------------------------*/

  //! Insert a new element with name name in the item at parentIndex and row. If
  //! row == -1, then appends at the end of the children list
  //!
  QModelIndex insertElement(QString name,
                            QModelIndex parentIndex,
                            int row = -1);

  bool readFile(const QFile& file);

  bool writeFile(const QFile& file);
  //!  Set the list of headers of the model. If the headers list is emty, there
  //!  will be only one column listing the elements by name. Otherwise,
  void setHeaders(const QStringList& headers);

  //! Getter method for m_elementHeader
  //!
  QString elementHeader() const;

  //! Setter method for m_elementHeader
  //!
  void setElementHeader(const QString& elementHeader);

 protected:
  //! Return the index node associated with the index
  //!
  AATreeNode_abstract* nodeFromIndex(const QModelIndex& index) const;

 protected:
  AATreeNode_abstract* m_rootNode = nullptr;

  //! List of headers that should be displayed. If not empty, the model will
  //! present attribute values ad data(). Otherwise it will present item names
  //! in first and only column
  QStringList m_headers = QStringList();

  //! If not empty, the first column will display the element name, and its
  //! header will be this string. Otherwise, (in column mode) the header will
  //! not be displayed.
  QString m_elementHeader = QString();
  bool showItemsInFirstColumn = true;
};

#endif  // AATREEMODEL_H
