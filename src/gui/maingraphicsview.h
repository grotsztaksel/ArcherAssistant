#ifndef MAINGRAPHICSVIEW_H
#define MAINGRAPHICSVIEW_H

#include <QGraphicsView>

struct hitMonitor {
  bool expectingRelease;
  QPoint leftClickPos;
};

class MainGraphicsView : public QGraphicsView {
  Q_OBJECT
 public:
  explicit MainGraphicsView(QWidget* parent = nullptr);

 signals:

 public slots:
  void fitView();

 protected:
  bool eventFilter(QObject* watched, QEvent* event) override;

  void zoom(int delta);

 protected:
  hitMonitor hit;
};

#endif  // MAINGRAPHICSVIEW_H
