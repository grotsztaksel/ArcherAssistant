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
  // Header:
  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
  QModelIndex index(int row,
                    int column,
                    const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& index) const override;

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  bool removeRows(int row,
                  int count,
                  const QModelIndex& parent = QModelIndex()) override;

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

  QModelIndex insertElement(QString name,
                            QModelIndex parentIndex,
                            int row = -1);

  bool readFile(const QFile& file);

  bool writeFile(const QFile& file);

  void setHeaders(const QStringList& headers);

  QString elementHeader() const;
  void setElementHeader(const QString& elementHeader);

 protected:
  //! Return the index node associated with the index
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
