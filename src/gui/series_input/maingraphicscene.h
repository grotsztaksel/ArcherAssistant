#ifndef MAINGRAPHICSCENE_H
#define MAINGRAPHICSCENE_H

#include <aatreemodel.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>

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
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

  //! Returns a pointer to the graphics item of given type at requested
  //! position, if such item is available otherwise returns nullptr
  QGraphicsItem* itemOfType(QPointF pos, int type);

 private:
  AATreeModel* m_model;
  QList<QGraphicsItem*> m_arrows;
  QGraphicsPixmapItem* m_photo;
  QTransform m_viewScale;
};

#endif  // MAINGRAPHICSCENE_H
