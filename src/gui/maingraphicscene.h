#ifndef MAINGRAPHICSCENE_H
#define MAINGRAPHICSCENE_H

#include <aatreemodel.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>

//! Use this enum to identify items in the scene
enum {
  Image = QGraphicsItem::UserType + 1,
  Arrow = QGraphicsItem::UserType + 2,
  TargetAreaCorner = QGraphicsItem::UserType + 3,
  TargetAreaEdgePoint = QGraphicsItem::UserType + 4,
  TargetAreaEdge = QGraphicsItem::UserType
};

class MainGraphicScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit MainGraphicScene(QObject* parent = nullptr);

  void setModel(AATreeModel* model);

  AATreeModel* model() const;
  QGraphicsItem* addHit(QPointF pos);

  void switchImage(const QString& path);
 signals:

 public slots:
  void setViewScale(const QTransform& viewScale);

  void zoom(qreal factor);

 protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

  //! Returns an item at position pos, or, if the item is grouped, an itemGroup
  //! to which this item belongs
  QGraphicsItem* complexItem(QPointF pos);

 private:
  AATreeModel* m_model;
  QList<QGraphicsItem*> m_arrows;
  QGraphicsPixmapItem* m_photo;
  QTransform m_viewScale;
};

#endif  // MAINGRAPHICSCENE_H
