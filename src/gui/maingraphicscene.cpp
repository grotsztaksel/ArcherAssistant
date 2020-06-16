#include "maingraphicscene.h"
#include "pointmarker.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QPixmap>

MainGraphicScene::MainGraphicScene(QObject* parent) : QGraphicsScene(parent) {}
void MainGraphicScene::setModel(AATreeModel* model) {
  m_model = model;
}

AATreeModel* MainGraphicScene::model() const {
  return m_model;
}

void MainGraphicScene::switchImage(const QString& path) {
  clear();
  m_photo = addPixmap(QPixmap::fromImage(QImage(path)));

  setSceneRect(m_photo->boundingRect());
}

void MainGraphicScene::zoom(qreal factor) {
  m_viewScale = QTransform();
  m_viewScale.scale(1 / factor, 1 / factor);
  for (auto item : m_arrows) {
    item->setTransform(m_viewScale, true);
  }
}
void MainGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  if (event->buttons() == Qt::LeftButton) {
    //    qDebug() << "-----------------------";
    auto gitem = itemAt(event->scenePos(), m_viewScale.inverted());
    //    qDebug() << "gitem" << gitem->data(0);

    //    PointMarker* item = dynamic_cast<PointMarker*>(gitem);
    //    qDebug() << "item" << item->data(0);
    //    qDebug() << "Position:" << event->scenePos();
    if (m_arrows.size() < 2) {
      auto item = qgraphicsitem_cast<PointMarker*>(addHit(event->scenePos()));
      sendEvent(item, event);
      return;
    }
    QGraphicsScene::mousePressEvent(event);
  } else {
    //    qDebug() << "Hey, a marker!" << item;
  }
}

QGraphicsItem* MainGraphicScene::complexItem(QPointF pos) {
  auto item = itemAt(pos, m_viewScale);
  QGraphicsItemGroup* group = item->group();
  qDebug() << group->data(0);
  if (group) {
    qDebug() << "Group!";
    return group;
  }
  return item;
}

void MainGraphicScene::setViewScale(const QTransform& viewScale) {
  QTransform inv = viewScale;
  QTransform my_t;
  my_t.scale(inv.m11(), inv.m11());
  m_viewScale = my_t;
}

QGraphicsItem* MainGraphicScene::addHit(QPointF pos) {
  PointMarker* newHit = new PointMarker();
  addItem(newHit);
  m_arrows.append(newHit);
  newHit->setPos(pos);

  //  // Take only scaling factors from the input matrix, to avoid
  //  shearing or
  //  // translating
  QTransform inv = m_viewScale.inverted();
  QTransform my_t;
  my_t.scale(inv.m11(), inv.m11());
  newHit->setTransform(my_t);
  newHit->setSelected(true);
  return newHit;
}
