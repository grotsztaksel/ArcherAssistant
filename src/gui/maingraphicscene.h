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
  bool addHit(QTransform viewportTransform, QPointF pos);
 signals:

 public slots:
  void switchImage(const QString& path);
  void zoom(qreal factor);

 private:
  AATreeModel* m_model;
  QList<QGraphicsItem*> m_arrows;
};

#endif  // MAINGRAPHICSCENE_H
