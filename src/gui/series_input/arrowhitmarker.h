#ifndef ARROWHITMARKER_H
#define ARROWHITMARKER_H

#include "pointmarker.h"

class ArrowHitMarker : public PointMarker {
 public:
  ArrowHitMarker(QGraphicsItem* parent = nullptr);

  QRectF boundingRect() const override;
  int type() const override;

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;
};

#endif  // ARROWHITMARKER_H
