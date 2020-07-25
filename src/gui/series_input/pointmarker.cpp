#include "pointmarker.h"

#include <QBrush>
#include <QDebug>

#include <QPainter>
#include <QPen>
#include "graphicsitems.h"

#include "maingraphicscene.h"

PointMarker::PointMarker(QGraphicsItem* parent) {
  setAcceptTouchEvents(true);
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemClipsChildrenToShape);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

QRectF PointMarker::boundingRect() const {
  return QRectF(-30, -30, 60, 60);
}

void PointMarker::paint(QPainter* painter,
                        const QStyleOptionGraphicsItem* option,
                        QWidget* widget) {
  QBrush brush(QColor(78, 97, 249));
  QPen pen(QColor(255, 255, 0));

  if (hovered) {
    brush.setColor(QColor(47, 58, 149));
  }
  if (isSelected()) {
    brush.setColor(Qt::red);
  }
  painter->setBrush(brush);
  painter->setPen(pen);
  painter->drawEllipse(boundingRect());
}

int PointMarker::type() const {
  return Point;
}

void PointMarker::setSelected(bool selected) {
  QGraphicsItem::setSelected(selected);
  if (!selected) {
    hovered = false;
  }
}

void PointMarker::setPos(const QPointF& pos) {
  auto sc = scene();
  MainGraphicScene* scene = qobject_cast<MainGraphicScene*>(sc);
  if (!scene) {
    return;
  }
  if (!scene->imageRect().contains(pos)) {
    return;
  }
  QGraphicsItem::setPos(pos);
}

void PointMarker::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  setSelected(true);
  setPos(event->scenePos());
  update();
}

void PointMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  setSelected(false);
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}

void PointMarker::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  if (event->buttons() == Qt::LeftButton) {
    setPos(event->scenePos());
  }
}

void PointMarker::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
  hovered = true;
  update();
}

void PointMarker::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
  hovered = false;
  update();
}
