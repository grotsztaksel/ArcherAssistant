#ifndef POINTMARKER_H
#define POINTMARKER_H

#include <QGraphicsItemGroup>

// A generic class for point objects in the graphics scene (frane anchors, arrow
// hits etc.)
class PointMarker : public QGraphicsItemGroup {
 public:
  PointMarker(QGraphicsItem* parent = nullptr);
  void draw();

 private:
  QGraphicsEllipseItem* m_circle;
};

#endif  // POINTMARKER_H
