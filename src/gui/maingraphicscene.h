#ifndef MAINGRAPHICSCENE_H
#define MAINGRAPHICSCENE_H

#include <aatreemodel.h>
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>

class MainGraphicScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit MainGraphicScene(QObject* parent = nullptr);

  void setModel(AATreeModel* model);

  AATreeModel* model() const;
 signals:

 public slots:
  void switchImage(const QString& path);

 private:
  AATreeModel* m_model;
};

#endif  // MAINGRAPHICSCENE_H
