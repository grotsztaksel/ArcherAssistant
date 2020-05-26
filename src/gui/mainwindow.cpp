#include "mainwindow.h"
#include "filemanagerwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  m_scene = new MainGraphicScene(this);
  ui->graphicsView->setScene(m_scene);
  m_scene->installEventFilter(ui->graphicsView);
  connect(ui->fitButton, SIGNAL(clicked()), ui->graphicsView, SLOT(fitView()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::connectWithCore(AACore* core) {
  m_core = core;
  m_model = core->model();
  ui->treeView->setModel(m_model);
  m_scene->setModel(m_model);
  connect(ui->treeView->selectionModel(),
          SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
          SLOT(onSelectionChanged(QItemSelection, QItemSelection)));
}

void MainWindow::on_actionGeneral_triggered() {
  FileManagerWindow* fmWindow = new FileManagerWindow(this, m_core);
  fmWindow->exec();
}

void MainWindow::on_actionAbout_Qt_triggered() {
  QMessageBox::aboutQt(this, "This sowtware is based on Qt library");
}

void MainWindow::on_actionAbout_triggered() {
  QString text;
  text += "Archer Assistant v 0.1";

  QMessageBox::about(this, "About Archer Assistant", text);
}

void MainWindow::on_actionSave_triggered() {
  m_model->writeFile(m_core->getSetting(CFG_FILE).toString());
}

void MainWindow::on_actionSave_as_triggered() {
  QString filename =
      QFileDialog::getSaveFileName(this, "Save database", QString(), "*.xml");
  if (filename.isEmpty()) {
    return;
  }

  m_core->settingsManager()->setupConfigFile(filename);
  on_actionSave_triggered();
}

void MainWindow::onSelectionChanged(const QItemSelection& selected,
                                    const QItemSelection& deselected) {
  // Pass information to the scene, if one item is selected, and it is a series
  // or image

  if (selected.size() != 1) {
    return;
  }

  for (QModelIndex index : selected.indexes()) {
    auto node = m_model->nodeFromIndex(index);
    if (node->name() == "image") {
      m_scene->switchImage(node->attribute("file").toString());
    }
  }
}
