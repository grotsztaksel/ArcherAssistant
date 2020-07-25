#include "maingraphicscene.h"
#include "arrowhitmarker.h"
#include "graphicsitems.h"
#include "pointmarker.h"
#include "seriesthumbnail.h"

#include <QDebug>
#include <QFile>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPixmap>
MainGraphicScene::MainGraphicScene(QObject* parent) : QGraphicsScene(parent) {}

void MainGraphicScene::setModel(AATreeModel* model) {
  m_model = model;
}

AATreeModel* MainGraphicScene::model() const {
  return m_model;
}

void MainGraphicScene::switchImage(QListWidgetItem* item) {
  clear();
  SeriesThumbnail* thumb = static_cast<SeriesThumbnail*>(item);
  if (!thumb) {
    return;
  }
  m_currentImage = thumb->node();
  QVariant pathattribute = m_currentImage->attribute("file");
  if (!pathattribute.isValid()) {
    return;
  }
  QString path = pathattribute.toString();
  if (path.isEmpty()) {
    return;
  }
  if (!QFile(path).exists()) {
    return;
  }
  m_photo = addPixmap(QPixmap::fromImage(QImage(path)));

  setSceneRect(m_photo->boundingRect());
}

QRectF MainGraphicScene::imageRect() {
  return m_photo->boundingRect();
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
    auto itemBelow = itemOfType(event->scenePos(), Point);
    if (!itemBelow) {
      auto item = qgraphicsitem_cast<PointMarker*>(addHit(event->scenePos()));
      if (item) {
        sendEvent(item, event);
        item->setSelected(false);
      }
    }
  }
  QGraphicsScene::mousePressEvent(event);
}

void MainGraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  auto point = itemOfType(event->scenePos(), Point);
  if (point) {
    sendEvent(point, event);
  }
}

void MainGraphicScene::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Delete) {
    for (auto item : selectedItems()) {
      removeItem(item);
      delete item;
    }
  } else if (event->key() == Qt::Key_Escape) {
    for (auto item : m_arrows) {
      item->setSelected(false);
    }
  }
}

QGraphicsItem* MainGraphicScene::itemOfType(QPointF pos, int type) {
  for (QGraphicsItem* item : items(pos)) {
    if (item->type() == type) {
      return item;
    }
  }
  return nullptr;
}

void MainGraphicScene::setViewScale(const QTransform& viewScale) {
  QTransform inv = viewScale;
  QTransform my_t;
  my_t.scale(inv.m11(), inv.m11());
  m_viewScale = my_t;
}

QGraphicsItem* MainGraphicScene::addHit(QPointF pos) {
  if (!m_photo || !imageRect().contains(pos)) {
    return nullptr;
  }
  PointMarker* newHit = new ArrowHitMarker(m_currentImage);
  addItem(newHit);
  m_arrows.append(newHit);
  newHit->setPos(pos);

  // Take only scaling factors from the input matrix, to avoid shearing or
  // translating
  QTransform inv = m_viewScale.inverted();
  QTransform my_t;
  my_t.scale(inv.m11(), inv.m11());
  newHit->setTransform(my_t);
  return newHit;
}
