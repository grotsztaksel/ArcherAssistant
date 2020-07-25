#ifndef ARROWHITMARKER_H
#define ARROWHITMARKER_H

#include "pointmarker.h"

class ArrowHitMarker : public PointMarker {
 public:
  ArrowHitMarker(QGraphicsScene* parentScene,
                 AATreeNode_abstract* parentNode,
                 AATreeNode_abstract* existingNode = nullptr,
                 QGraphicsItem* parent = nullptr);
  QRectF boundingRect() const override;

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;
};

#endif  // ARROWHITMARKER_H
