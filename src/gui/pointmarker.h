#ifndef POINTMARKER_H
#define POINTMARKER_H

#include <QGraphicsItemGroup>

class PointMarker : public QGraphicsItemGroup {
 public:
  PointMarker(QGraphicsItem* parent = nullptr);
  void draw();

 private:
  QGraphicsEllipseItem* m_circle;
};

#endif  // POINTMARKER_H
