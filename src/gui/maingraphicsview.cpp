#include "maingraphicsview.h"

#include <qevent.h>
#include <QDebug>
#include <QEvent>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>
MainGraphicsView::MainGraphicsView(QWidget* parent) : QGraphicsView(parent) {
  setDragMode(QGraphicsView::RubberBandDrag);
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
  if (event->type() == QEvent::GraphicsSceneWheel) {
    // Zoom
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QGraphicsSceneWheelEvent* wheelEvent =
        static_cast<QGraphicsSceneWheelEvent*>(event);
    int delta = wheelEvent->delta();
    zoom(delta);
  } else if (event->type() == QEvent::GraphicsSceneMousePress) {
    QGraphicsSceneMouseEvent* mouseEvent =
        static_cast<QGraphicsSceneMouseEvent*>(event);
    if (mouseEvent->buttons() == Qt::MidButton) {
      // Pan the view
      setDragMode(QGraphicsView::ScrollHandDrag);
      // emit a left mouse click (the default button for the drag mode)
      // Thank you Gordon Boer(Legor)
      // (https://gist.github.com/Legor/a00760b6d7af32c01357fb7ff76ad86a)
      QMouseEvent* pressEvent = new QMouseEvent(
          QEvent::GraphicsSceneMousePress, mapFromScene(mouseEvent->scenePos()),
          Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton,
          Qt::KeyboardModifier::NoModifier);
      mousePressEvent(pressEvent);
    }
  } else if (event->type() == QEvent::GraphicsSceneMouseRelease) {
    setDragMode(QGraphicsView::RubberBandDrag);

  } else {
    return QGraphicsView::eventFilter(watched, event);
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
