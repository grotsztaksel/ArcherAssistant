#include "mainwindow.h"
#include "filemanagerwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::connectWithCore(AACore* core) {
  m_core = core;
  m_model = core->model();
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
