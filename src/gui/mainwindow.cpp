#include "mainwindow.h"
#include <QDebug>
#include "stdio.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QSettings* settings =
      new QSettings(QSettings::UserScope, "Home", "ArcherAssistant", this);
  if (settings->contains("configFile")) {
    qDebug() << "Config file in Window:" << settings->value("configFile");
  }
  connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(onLoadClicked()));
  connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
  connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddClicked()));
  connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(onRemoveClicked()));
}

void MainWindow::onLoadClicked() {
  qDebug() << "Setting model";
  m_model = new AATreeModel(this);
  QSettings* settings =
      new QSettings(QSettings::UserScope, "Home", "ArcherAssistant", this);
  QFile file;
  file.setFileName(settings->value("configFile").toString());
  m_model->readFile(file);
  ui->treeView->setModel(m_model);
  qDebug() << m_model->rowCount();
}
void MainWindow::onSaveClicked() {
  QFile file;
  file.setFileName(
      "c:/Users/piotr/Documents/ArcherAssistant/raw_results/config_copy.xml");
  qDebug() << "Saving stuff";
  m_model->writeFile(file);
}

void MainWindow::onAddClicked() {
  auto parentIndex = ui->treeView->currentIndex().parent();
  int currentRow = ui->treeView->currentIndex().row();
  m_model->insertElement("newItem", parentIndex, currentRow + 1);
}

void MainWindow::onRemoveClicked() {}
MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::connectDataManager(Worker* mgr) {
  mgr->sayHello();
}
