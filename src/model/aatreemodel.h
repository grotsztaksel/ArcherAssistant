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

 protected:
  static AATreeNode_abstract* nodeFromIndex(const QModelIndex& index);
  AATreeNode_abstract* m_rootNode = nullptr;
};

#endif  // AATREEMODEL_H
