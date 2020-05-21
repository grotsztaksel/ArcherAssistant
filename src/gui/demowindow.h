#ifndef DEMOWINDOW_H
#define DEMOWINDOW_H

#include <QMainWindow>

#include <gui/trainingsessionwindow.h>
#include "aacore.h"

#include <aatreemodel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class DemoWindow;
}
QT_END_NAMESPACE

class DemoWindow : public QMainWindow {
  Q_OBJECT

 public:
  DemoWindow(QWidget* parent = nullptr);
  ~DemoWindow();

  void connectWithCore(AACore* core);

 protected slots:
  void onLoadClicked();
  void onSaveClicked();
  void onAddClicked();
  void onRemoveClicked();
  void onUpClicked();
  void onDownClicked();

 protected:
  //! Move item down by one. If it is the last in its parent, move it to the
  //! beginnig of the next node on parent level
  //!
  bool moveDown(QModelIndex index);

  //! Move item up by one. If it is the first in its parent, move it to the end
  //! of the previous node on parent level
  //!
  bool moveUp(QModelIndex index);

 private:
  Ui::DemoWindow* ui;

  TrainingSessionWindow* tsWindow;

  AATreeModel* m_model;
};
#endif  // DEMOWINDOW_H
