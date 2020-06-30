#ifndef SERIESINPUTWIDGET_H
#define SERIESINPUTWIDGET_H

#include <QListWidget>
#include <QWidget>
#include "aaobject.h"
#include "aatreemodel.h"
#include "maingraphicscene.h"
namespace Ui {
class SeriesInputWidget;
}

class SeriesInputWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SeriesInputWidget(AATreeModel* model,
                             AATreeNode_abstract* node,
                             AAObject* settingsManager,
                             QWidget* parent = nullptr);
  ~SeriesInputWidget();

 private slots:
  void updateThumbnails();
  void onImageSelected(QListWidgetItem* item);

 private:
  Ui::SeriesInputWidget* ui;

  MainGraphicScene* m_scene;
  AATreeModel* m_model;
  AATreeNode_abstract* m_seriesNode;
  AAObject* m_settingsMgr;

  QHash<QListWidgetItem*, AATreeNode_abstract*> m_map;
  AATreeNode_abstract* currentImageNode;
};

#endif  // SERIESINPUTWIDGET_H
