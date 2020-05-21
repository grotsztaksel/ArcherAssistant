#include "mainwindow.h"
#include "filemanagerwindow.h"
#include "ui_mainwindow.h"

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
