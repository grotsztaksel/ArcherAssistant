#include "hitmarker.h"

#include <QBrush>
#include <QPen>

#include <QDebug>
HitMarker::HitMarker(QGraphicsItem* parent) : QGraphicsItemGroup(parent) {
  draw();
}

void HitMarker::draw() {
  m_circle = new QGraphicsEllipseItem(-4, -4, 8, 8, this);
  m_circle->setBrush(QBrush(QColor(Qt::red)));
  m_circle->setPen(QPen(QColor(Qt::black)));

  for (int i = 0; i < 3; i++) {
    QGraphicsLineItem* line = new QGraphicsLineItem(0, 0, 30, 0, this);
    line->setPen(QPen(QColor(Qt::black)));
    QTransform t;
    t.rotate(i * 120);
    line->setTransform(t);
    addToGroup(line);
  }
  addToGroup(m_circle);
}
