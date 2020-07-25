#include "arrowhitmarker.h"

#include "graphicsitems.h"
#include "maingraphicscene.h"

#include <QBrush>
#include <QDebug>

#include <QPainter>
#include <QPen>

ArrowHitMarker::ArrowHitMarker(QGraphicsScene* parentScene,
                               AATreeNode_abstract* imageNode,
                               AATreeNode_abstract* existingHitNode,
                               QGraphicsItem* parent)
    : PointMarker(parent), m_hitNode{existingHitNode} {
  if (!m_hitNode) {
    m_hitNode = imageNode->addChild("hit");
  }
  m_parentScene = qobject_cast<MainGraphicScene*>(parentScene);
}

ArrowHitMarker::~ArrowHitMarker() {
  auto parent = m_hitNode->parent();
  int row = m_hitNode->getIndex();
  parent->removeChild(row);
}

QRectF ArrowHitMarker::boundingRect() const {
  return QRectF(-12, -12, 24, 24);
}

int ArrowHitMarker::type() const {
  return Point;
}

void ArrowHitMarker::setPos(const QPointF& pos) {
  qDebug() << "ARROW! setting pos" << pos;
  QGraphicsItem::setPos(pos);
  m_hitNode->setAttribute("X", pos.x());
  m_hitNode->setAttribute("Y", pos.y());
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

  //  painter->setBrush(brush);
  painter->drawEllipse(QPointF(0, 0), bR.top() * smallerCirc,
                       bR.right() * smallerCirc);
  pen.setWidth(1);
  pen.setColor(Qt::black);
  painter->setPen(pen);
  painter->drawLine(0, bR.top() * lineExt, 0, bR.bottom() * lineExt);
  painter->drawLine(bR.left() * lineExt, 0, bR.right() * lineExt, 0);
}

QVariant ArrowHitMarker::itemChange(QGraphicsItem::GraphicsItemChange change,
                                    const QVariant& value) {
  if (change == ItemScenePositionHasChanged) {
    QPointF pos = m_parentScene->posRelativeToImage(this);
    m_hitNode->setAttribute("X", pos.x());
    m_hitNode->setAttribute("Y", pos.y());
  }
  return QGraphicsItem::itemChange(change, value);
}
