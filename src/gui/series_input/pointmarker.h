#ifndef POINTMARKER_H
#define POINTMARKER_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

// A generic class for point objects in the graphics scene (frane anchors, arrow
// hits etc.)
class PointMarker : public QGraphicsItem {
 public:
  PointMarker(QGraphicsItem* parent = nullptr);
  QRectF boundingRect() const override;
  int type() const override;

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

 protected:
  bool hovered = false;
  bool pressed = false;
};

#endif  // POINTMARKER_H
