#include "arrowhitmarker.h"

#include "graphicsitems.h"

#include <QBrush>
#include <QDebug>

#include <QPainter>
#include <QPen>

ArrowHitMarker::ArrowHitMarker(QGraphicsScene* parentScene,
                               AATreeNode_abstract* imageNode,
                               AATreeNode_abstract* existingNode,
                               QGraphicsItem* parent)
    : PointMarker(parentScene, imageNode, existingNode, parent) {}

QRectF ArrowHitMarker::boundingRect() const {
  return QRectF(-12, -12, 24, 24);
}

int ArrowHitMarker::type() const {
  return Point;
}

void ArrowHitMarker::paint(QPainter* painter,
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
  painter->drawEllipse(bR);
  pen.setColor(myYellow);

  painter->setBrush(QBrush(Qt::NoBrush));

  painter->setPen(pen);
  const double lineExt = 1.2;
  const double smallerCirc = 0.55;

  pen.setWidth(4);
  pen.setColor(myYellow);

  if (hovered) {
    pen.setColor(myOrange);
  }
  if (isSelected()) {
    pen.setColor(Qt::red);
  }

  painter->setPen(pen);

  painter->drawEllipse(QPointF(0, 0), bR.top() * smallerCirc,
                       bR.right() * smallerCirc);
  pen.setWidth(1);
  pen.setColor(Qt::black);
  painter->setPen(pen);
  painter->drawLine(0, bR.top() * lineExt, 0, bR.bottom() * lineExt);
  painter->drawLine(bR.left() * lineExt, 0, bR.right() * lineExt, 0);
}
