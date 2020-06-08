#ifndef MAINGRAPHICSCENE_H
#define MAINGRAPHICSCENE_H

#include <aatreemodel.h>
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>

class MainGraphicScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit MainGraphicScene(QObject* parent = nullptr);

  void setModel(AATreeModel* model);

  AATreeModel* model() const;
  bool addHit(QPointF pos);

 signals:

 public slots:
  void setViewScale(const QTransform& viewScale);
  void switchImage(const QString& path);
  void zoom(qreal factor);

 protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event);

 private:
  AATreeModel* m_model;
  QList<QGraphicsItem*> m_arrows;
  QTransform m_viewScale;
};

#endif  // MAINGRAPHICSCENE_H
