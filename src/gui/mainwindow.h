#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aacore.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  void connectWithCore(AACore* core);

 private slots:
  void on_actionGeneral_triggered();

  void on_actionAbout_Qt_triggered();

  void on_actionAbout_triggered();

  void on_actionSave_triggered();

  void on_actionSave_as_triggered();

 private:
  Ui::MainWindow* ui;

  AATreeModel* m_model;

  AACore* m_core;
};

#endif  // MAINWINDOW_H
