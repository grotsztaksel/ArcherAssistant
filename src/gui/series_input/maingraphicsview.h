#ifndef MAINGRAPHICSVIEW_H
#define MAINGRAPHICSVIEW_H

#include <QGraphicsView>

class MainGraphicsView : public QGraphicsView {
  Q_OBJECT
 public:
  explicit MainGraphicsView(QWidget* parent = nullptr);

 signals:
  void zoomed(qreal factor);
 public slots:
  void fitView();

 protected:
  bool eventFilter(QObject* watched, QEvent* event) override;

  void zoom(int delta);

 protected:
  bool midButtonPressed = false;
};

#endif  // MAINGRAPHICSVIEW_H
