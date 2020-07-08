#ifndef SERIESINPUTPROXYMODEL_H
#define SERIESINPUTPROXYMODEL_H

#include <aatreemodel.h>
#include <QSortFIlterProxyModel>

class SeriesInputProxyModel : public QSortFilterProxyModel {
 public:
  SeriesInputProxyModel(QObject* parent = nullptr);

  void setSourceModel(QAbstractItemModel* sourceModel) override;
  bool filterAcceptsRow(int source_row,
                        const QModelIndex& source_parent) const override;

 private:
  AATreeModel* m_sourceModel;
};

#endif  // SERIESINPUTPROXYMODEL_H
