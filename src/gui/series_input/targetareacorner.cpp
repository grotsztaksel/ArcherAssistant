#include "targetareacorner.h"

#include "graphicsitems.h"

#include <QBrush>
#include <QDebug>

#include <QPainter>
#include <QPen>

TargetAreaCorner::TargetAreaCorner(QGraphicsScene* parentScene,
                                   AATreeNode_abstract* parentNode,
                                   AATreeNode_abstract* existingNode,
                                   QGraphicsItem* parent)
    : PointMarker(parentScene, parentNode, existingNode, parent) {
  m_nodeName = "point";
  createNode(parentNode);
}

QRectF TargetAreaCorner::boundingRect() const {
  return QRectF(-12, -12, 24, 24);
}

void TargetAreaCorner::paint(QPainter* painter,
                             const QStyleOptionGraphicsItem* option,
                             QWidget* widget) {
  const QRectF bR = boundingRect();
  QBrush brush(QColor(0, 255, 64));

  QPen pen(QColor(0, 0, 0));
  QColor myOrange(247, 150, 70);
  QColor myYellow = QColor(255, 255, 0);
  pen.setWidth(3);

  pen.setColor(QColor(Qt::black));
  painter->setPen(pen);
  painter->setBrush(brush);
  painter->drawEllipse(bR);

  if (hovered) {
    pen.setColor(myOrange);
  }
  if (isSelected()) {
    pen.setColor(Qt::red);
  }
}
