#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelection>
#include <QMainWindow>
#include "aacore.h"
#include "seriesinputproxymodel.h"

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
  void onSelectionChanged(const QItemSelection& selected,
                          const QItemSelection& deselected);

  void on_actionProgram_settings_triggered();

  void on_actionOpen_Project_triggered();

 private:
  Ui::MainWindow* ui;

  AATreeModel* m_model;
  SeriesInputProxyModel* m_proxyModel;
  AACore* m_core;
};

#endif  // MAINWINDOW_H
