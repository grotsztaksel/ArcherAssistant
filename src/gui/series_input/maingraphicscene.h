#ifndef MAINGRAPHICSCENE_H
#define MAINGRAPHICSCENE_H

#include <aatreemodel.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>
#include <QListWidgetItem>

class MainGraphicScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit MainGraphicScene(QObject* parent = nullptr);

  void setModel(AATreeModel* model);

  AATreeModel* model() const;
  QGraphicsItem* addHit(QPointF pos, AATreeNode_abstract* hit = nullptr);

  void switchImage(QListWidgetItem* item);
  QRectF imageRect();

  void createMarkersForExistingHits();

  //! Get the position expressed in fraction of widh and height of the image in
  //! the scene The origin is top left corner of the image
  QPointF posRelativeToImage(QGraphicsItem* item);
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
  //! Place the given hit marker at a position relative to the image bounds
  //! @param hit - a pointer to the graphics item that should be positioned
  //!              relative to the image
  //! @param x - number from 0 to 1, indicating the relative horizontal position
  //! @param y - number from 0 to 1, indicating the relative vertical position
  void placeOnImage(AATreeNode_abstract* hit, const double x, const double y);

 private:
  AATreeModel* m_model;
  AATreeNode_abstract* m_currentImage;
  QList<QGraphicsItem*> m_arrows;
  QGraphicsPixmapItem* m_photo;
  QTransform m_viewScale;
};

#endif  // MAINGRAPHICSCENE_H
