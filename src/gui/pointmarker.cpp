#include "pointmarker.h"

#include <QBrush>
#include <QPen>
#include "maingraphicscene.h"

#include <QDebug>
PointMarker::PointMarker(QGraphicsItem* parent) : QGraphicsItemGroup(parent) {
  setAcceptTouchEvents(true);
  setAcceptHoverEvents(true);

  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemClipsChildrenToShape);
  draw();
  setData(0, "Arrow");
}

void PointMarker::draw() {
  m_circle = new QGraphicsEllipseItem(-32, -32, 64, 64, this);
  m_circle->setBrush(QBrush(QColor(230, 230, 0, 128)));
  m_circle->setPen(QPen(QColor(Qt::NoPen)));
  m_circle->setData(0, "MainElips");
  addToGroup(m_circle);
  auto nock = new QGraphicsEllipseItem(-4, -4, 8, 8, this);
  nock->setBrush(QBrush(QColor(Qt::red)));
  nock->setPen(QPen(QColor(Qt::black)));
  nock->setData(0, "nock");
  addToGroup(nock);
  for (int i = 0; i < 3; i++) {
    QGraphicsLineItem* line = new QGraphicsLineItem(0, 0, 30, 0, this);
    line->setPen(QPen(QColor(Qt::black)));
    QTransform t;
    t.rotate(i * 120);
    line->setTransform(t);
    line->setData(0, "Vane" + QString(i));
    addToGroup(line);
  }
}

void PointMarker::highlight(bool onoff) {
  if (onoff) {
    m_circle->setBrush(QBrush(QColor(0, 230, 200, 128)));
  } else {
    m_circle->setBrush(QBrush(QColor(230, 230, 0, 128)));
  }
}

int PointMarker::type() const {
  return Arrow;
}

QRectF PointMarker::boundingRect() const {
  return m_circle->boundingRect();
}

void PointMarker::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  setSelected(true);
}

void PointMarker::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  setPos(event->scenePos());
}

void PointMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  setSelected(false);
}

void PointMarker::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
  highlight(true);
}

void PointMarker::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
  highlight(false);
}
