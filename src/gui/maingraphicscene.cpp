#include "maingraphicscene.h"
#include "hitmarker.h"

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
  QTransform t;
  t.scale(1 / factor, 1 / factor);
  for (auto item : m_arrows) {
    item->setTransform(t, true);
  }
}

bool MainGraphicScene::addHit(QTransform viewportTransform, QPointF pos) {
  HitMarker* newHit = new HitMarker();
  addItem(newHit);
  m_arrows.append(newHit);
  newHit->setPos(pos);

  // Take only scaling factors from the input matrix, to avoid shearing or
  // translating
  QTransform inv = viewportTransform.inverted();
  QTransform my_t;
  my_t.scale(inv.m11(), inv.m11());
  newHit->setTransform(my_t);

  newHit->setFlag(QGraphicsItem::ItemIsMovable);
  return true;
}
