#ifndef ARROWHITMARKER_H
#define ARROWHITMARKER_H

#include "aatreenode_abstract.h"
#include "maingraphicscene.h"
#include "pointmarker.h"

class ArrowHitMarker : public PointMarker {
 public:
  ArrowHitMarker(QGraphicsScene* parentScene,
                 AATreeNode_abstract* imageNode,
                 AATreeNode_abstract* existingHitNode = nullptr,
                 QGraphicsItem* parent = nullptr);
  ~ArrowHitMarker();
  QRectF boundingRect() const override;
  int type() const override;

  void setPos(const QPointF& pos);

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;

  QVariant itemChange(GraphicsItemChange change,
                      const QVariant& value) override;
  AATreeNode_abstract* m_hitNode = nullptr;
  MainGraphicScene* m_parentScene = nullptr;
};

#endif  // ARROWHITMARKER_H
