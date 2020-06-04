#ifndef HITMARKER_H
#define HITMARKER_H

#include <QGraphicsItemGroup>

class HitMarker : public QGraphicsItemGroup {
 public:
  HitMarker(QGraphicsItem* parent = nullptr);
  void draw();

  void setPos(const QPointF& pos);
  void setPos(qreal x, qreal y);

 private:
  QGraphicsEllipseItem* m_circle;
};

#endif  // HITMARKER_H
