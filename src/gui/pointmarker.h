#ifndef POINTMARKER_H
#define POINTMARKER_H

#include <QGraphicsItemGroup>

// A generic class for point objects in the graphics scene (frane anchors, arrow
// hits etc.)
class PointMarker : public QGraphicsItemGroup {
 public:
  PointMarker(QGraphicsItem* parent = nullptr);
  void draw();
  void highlight(bool onoff);

  int type() const override;
  QRectF boundingRect() const override;

 private:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
  QGraphicsEllipseItem* m_circle;
};

#endif  // POINTMARKER_H
