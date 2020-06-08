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
  auto image = addPixmap(QPixmap::fromImage(QImage(path)));
  setSceneRect(image->boundingRect());
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
    qDebug() << "And hit!";
    addHit(event->scenePos());
  }
}

void MainGraphicScene::setViewScale(const QTransform& viewScale) {
  QTransform inv = viewScale.inverted();
  QTransform my_t;
  my_t.scale(inv.m11(), inv.m11());
  m_viewScale = my_t;
}

bool MainGraphicScene::addHit(QPointF pos) {
  PointMarker* newHit = new PointMarker();
  addItem(newHit);
  m_arrows.append(newHit);
  newHit->setPos(pos);

  //  // Take only scaling factors from the input matrix, to avoid shearing or
  //  // translating
  //  QTransform inv = viewportTransform.inverted();
  //  QTransform my_t;
  //  my_t.scale(inv.m11(), inv.m11());
  newHit->setTransform(m_viewScale);

  return true;
}
