#ifndef ARROWHITMARKER_H
#define ARROWHITMARKER_H

#include "pointmarker.h"

class ArrowHitMarker : public PointMarker {
 public:
  ArrowHitMarker(QGraphicsScene* parentScene,
                 AATreeNode_abstract* imageNode,
                 AATreeNode_abstract* existingNode = nullptr,
                 QGraphicsItem* parent = nullptr);
  QRectF boundingRect() const override;
  int type() const override;

  void setPos(const QPointF& pos);

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;

 private:
  const QString m_nodeName = "hit";
};

#endif  // ARROWHITMARKER_H
