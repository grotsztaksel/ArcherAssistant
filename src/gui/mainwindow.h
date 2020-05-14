#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <gui/trainingsessionwindow.h>
#include "worker.h"

#include <aatreemodel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void connectDataManager(Worker* mgr);

 protected slots:
  void onLoadClicked();
  void onSaveClicked();
  void onAddClicked();
  void onRemoveClicked();

 private:
  Ui::MainWindow* ui;

  TrainingSessionWindow* tsWindow;

  AATreeModel* m_model;
};
#endif  // MAINWINDOW_H
