#include <qevent.h>
#include <QDebug>
#include <QEvent>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>

#include "hitmarker.h"
#include "maingraphicsview.h"

MainGraphicsView::MainGraphicsView(QWidget* parent) : QGraphicsView(parent) {
  setDragMode(QGraphicsView::RubberBandDrag);
  setAttribute(Qt::WA_AcceptTouchEvents, true);
}

void MainGraphicsView::fitView() {
  QRectF bound;
  for (auto item : items()) {
    bound = bound.united(item->sceneBoundingRect());
  }
  fitInView(bound, Qt::KeepAspectRatio);
}

bool MainGraphicsView::eventFilter(QObject* watched, QEvent* event) {
  if (watched != scene()) {
    return false;
  }
  hit.expectingRelease = false;
  switch (event->type()) {
    case QEvent::GraphicsSceneWheel: {
      // Zoom
      setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
      QGraphicsSceneWheelEvent* wheelEvent =
          static_cast<QGraphicsSceneWheelEvent*>(event);
      int delta = wheelEvent->delta();
      zoom(delta);
      break;
    }
    case QEvent::TabletPress:
    case QEvent::TabletMove:
    case QEvent::TabletRelease:
    case QEvent::TabletEnterProximity:
    case QEvent::TabletLeaveProximity:
    case QEvent::TabletTrackingChange: {
      qDebug() << "A tablef";
      QTabletEvent* tabEvent = static_cast<QTabletEvent*>(event);
      if (tabEvent->pointerType() == QTabletEvent::Pen) {
        QMouseEvent* pressEvent = new QMouseEvent(
            QEvent::GraphicsSceneMousePress, mapFromScene(tabEvent->posF()),
            Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton,
            Qt::KeyboardModifier::NoModifier);
        mousePressEvent(pressEvent);
      }
      break;
    }
    case QEvent::TouchBegin: {
      qDebug() << "Oh, touch!";
      break;
    }
    case QEvent::TouchEnd: {
      qDebug() << "End touch!";
      break;
    }
    case QEvent::GraphicsSceneMousePress: {
      QGraphicsSceneMouseEvent* mouseEvent =
          static_cast<QGraphicsSceneMouseEvent*>(event);
      switch (mouseEvent->buttons()) {
        case Qt::LeftButton: {
          if (midButtonPressed) {
            break;
          }
          qDebug() << "New Arrow";
          addHit(mouseEvent->scenePos());
          break;
        }
        case Qt::MidButton: {
          // Pan the view
          midButtonPressed = true;
          setDragMode(QGraphicsView::ScrollHandDrag);
          // emit a left mouse click (the default button for the drag mode)
          // Thank you Gordon Boer(Legor)
          // (https://gist.github.com/Legor/a00760b6d7af32c01357fb7ff76ad86a)
          QMouseEvent* pressEvent = new QMouseEvent(
              QEvent::GraphicsSceneMousePress,
              mapFromScene(mouseEvent->scenePos()), Qt::MouseButton::LeftButton,
              Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
          mousePressEvent(pressEvent);
          break;
        } break;
      }
      break;
    }
    case QEvent::GraphicsSceneMouseRelease: {
      midButtonPressed = false;
      QGraphicsSceneMouseEvent* mouseEvent =
          static_cast<QGraphicsSceneMouseEvent*>(event);
      qDebug() << "Released!" << mouseEvent->screenPos();
      setDragMode(QGraphicsView::RubberBandDrag);
      break;
    }
    default: {
      return QGraphicsView::eventFilter(watched, event);
      break;
    }
  }
  return true;
}
void MainGraphicsView::zoom(int delta) {
  qreal factor = 1.15;
  if (delta >= 0) {
    scale(factor, factor);
  } else {
    scale(1 / factor, 1 / factor);
  }
}

void MainGraphicsView::addHit(QPointF pos) {
  HitMarker* newHit = new HitMarker();
  scene()->addItem(newHit);
  newHit->setPos(pos);
}
