#include "maingraphicscene.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QPixmap>
void MainGraphicScene::setModel(AATreeModel* model) {
  m_model = model;
}

MainGraphicScene::MainGraphicScene(QObject* parent) : QGraphicsScene(parent) {}

AATreeModel* MainGraphicScene::model() const {
  return m_model;
}

void MainGraphicScene::switchImage(const QString& path) {
  clear();
  auto image = addPixmap(QPixmap::fromImage(QImage(path)));
  setSceneRect(image->boundingRect());
}
