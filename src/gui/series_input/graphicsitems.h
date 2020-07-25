#ifndef GRAPHICSITEMS_H
#define GRAPHICSITEMS_H

#include <QGraphicsItem>

//! Use this enum to identify items in the scene
enum {
  Image = QGraphicsItem::UserType + 1,
  Point = QGraphicsItem::UserType + 2,
  Arrow = QGraphicsItem::UserType + 3,
  TargetAreaCornerPoint = QGraphicsItem::UserType + 4,
  TargetAreaEdgePoint = QGraphicsItem::UserType + 5,
  TargetAreaEdge = QGraphicsItem::UserType + 6
};
#endif  // GRAPHICSITEMS_H
