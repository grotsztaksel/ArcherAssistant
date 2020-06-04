#include "hitmarker.h"

#include <QBrush>
#include <QPen>

#include <QDebug>
HitMarker::HitMarker(QGraphicsItem* parent) : QGraphicsItemGroup(parent) {
  draw();
}

void HitMarker::draw() {
  m_circle = new QGraphicsEllipseItem(0, 0, 4, 4);
  m_circle->setBrush(QBrush(QColor(Qt::red)));
  m_circle->setPen(QPen(QColor(Qt::black)));
  addToGroup(m_circle);
}

void HitMarker::setPos(const QPointF& pos) {
  qDebug() << "Setting pos of me" << pos;
  m_circle->setPos(pos);
}

void HitMarker::setPos(qreal x, qreal y) {
  setPos(QPointF(x, y));
}
