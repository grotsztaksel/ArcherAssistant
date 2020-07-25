#ifndef POINTMARKER_H
#define POINTMARKER_H

#include "maingraphicscene.h"

#include <aatreenode_abstract.h>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

// A generic class for point objects in the graphics scene (frane anchors, arrow
// hits etc.)
class PointMarker : public QGraphicsItem {
 public:
  PointMarker(QGraphicsScene* parentScene,
              AATreeNode_abstract* parentNode,
              AATreeNode_abstract* existingNode = nullptr,
              QGraphicsItem* parent = nullptr);
  ~PointMarker();

  QRectF boundingRect() const override;
  int type() const override;

  void setSelected(bool selected);

  void setPos(const QPointF& pos);

  QVariant itemChange(QGraphicsItem::GraphicsItemChange change,
                      const QVariant& value) override;

  QString nodeName();

 protected:
  void paint(QPainter* painter,
             const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

  void createNode(AATreeNode_abstract* parentNode);

 protected:
  bool hovered = false;

  AATreeNode_abstract* m_node = nullptr;
  MainGraphicScene* m_parentScene = nullptr;

  QString m_nodeName;
};

#endif  // POINTMARKER_H
