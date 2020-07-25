#ifndef TARGETAREACORNER_H
#define TARGETAREACORNER_H

#include "pointmarker.h"

class TargetAreaCorner : public PointMarker {
 public:
  TargetAreaCorner(QGraphicsScene* parentScene,
                   AATreeNode_abstract* parentNode,
                   AATreeNode_abstract* existingNode = nullptr,
                   QGraphicsItem* parent = nullptr);
  QRectF boundingRect() const override;

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;
};
#endif  // TARGETAREACORNER_H
