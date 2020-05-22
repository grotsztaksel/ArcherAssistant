#ifndef PATHVIEWPROXYMODEL_H
#define PATHVIEWPROXYMODEL_H

#include "QSortFIlterProxyModel.h"

class pathViewModel : public QSortFilterProxyModel {
  Q_OBJECT
 public:
  explicit pathViewModel(QObject* parent = nullptr);
  bool filterAcceptsRow(int source_row,
                        const QModelIndex& source_parent) const override;
  QModelIndex parent(const QModelIndex& index);
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

 private:
  const QString m_parentName;
};

#endif  // PATHVIEWPROXYMODEL_H
