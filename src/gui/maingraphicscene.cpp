#include "maingraphicscene.h"

#include <QPixmap>

void MainGraphicScene::setModel(AATreeModel* model) {
  m_model = model;
}

MainGraphicScene::MainGraphicScene(QObject* parent) : QGraphicsScene(parent) {}

AATreeModel* MainGraphicScene::model() const {
  return m_model;
}

void MainGraphicScene::showImage(const QString& path) {
  clear();
  addPixmap(QPixmap::fromImage(QImage(path)));
}
