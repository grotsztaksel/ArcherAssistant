#include "pointmarker.h"

#include <QBrush>
#include <QDebug>

#include <QPainter>
#include <QPen>
#include "graphicsitems.h"

#include "maingraphicscene.h"

PointMarker::PointMarker(QGraphicsScene* parentScene,
                         AATreeNode_abstract* parentNode,
                         AATreeNode_abstract* existingNode,
                         QGraphicsItem* parent)
    : QGraphicsItem(parent), m_node{existingNode} {
  m_parentScene = qobject_cast<MainGraphicScene*>(parentScene);

  setAcceptTouchEvents(true);
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemClipsChildrenToShape);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

PointMarker::~PointMarker() {
  auto parent = m_node->parent();
  int row = m_node->getIndex();
  parent->removeChild(row);
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

QVariant PointMarker::itemChange(QGraphicsItem::GraphicsItemChange change,
                                 const QVariant& value) {
  if (change == ItemScenePositionHasChanged) {
    QPointF pos = m_parentScene->posRelativeToImage(this);
    m_node->setAttribute("X", pos.x());
    m_node->setAttribute("Y", pos.y());
  }
  return QGraphicsItem::itemChange(change, value);
}

void PointMarker::createNode(AATreeNode_abstract* parentNode) {
  if (m_node || !parentNode) {
    return;
  }
  m_node = parentNode->addChild(this->nodeName());
}

QString PointMarker::nodeName() {
  return m_nodeName;
}
