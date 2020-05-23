#ifndef MAINGRAPHICSCENE_H
#define MAINGRAPHICSCENE_H

#include <aatreemodel.h>
#include <QGraphicsScene>

class MainGraphicScene : public QGraphicsScene {
  Q_OBJECT
 public:
  explicit MainGraphicScene(QObject* parent = nullptr);

  void setModel(AATreeModel* model);

  AATreeModel* model() const;

 public slots:
  void showImage(const QString& path);
 signals:
 private:
  AATreeModel* m_model;
};

#endif  // MAINGRAPHICSCENE_H
