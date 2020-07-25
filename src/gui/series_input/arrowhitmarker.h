#ifndef ARROWHITMARKER_H
#define ARROWHITMARKER_H

#include "aatreenode_abstract.h"
#include "pointmarker.h"

class ArrowHitMarker : public PointMarker {
 public:
  ArrowHitMarker(AATreeNode_abstract* imageNode,
                 QGraphicsItem* parent = nullptr);

  QRectF boundingRect() const override;
  int type() const override;

  void setPos(const QPointF& pos);

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;
  AATreeNode_abstract* m_hitNode;
};

#endif  // ARROWHITMARKER_H
