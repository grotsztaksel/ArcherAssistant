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
  connect(ui->downButton, SIGNAL(clicked()), this, SLOT(onDownClicked()));
  connect(ui->upButton, SIGNAL(clicked()), this, SLOT(onUpClicked()));
}

void MainWindow::onLoadClicked() {
  m_model = new AATreeModel(this);
  QSettings* settings =
      new QSettings(QSettings::UserScope, "Home", "ArcherAssistant", this);
  QFile file;
  file.setFileName(settings->value("configFile").toString());
  m_model->readFile(file);
  auto headers = QStringList() << "name"
                               << "score"
                               << "diameter"
                               << "width";
  m_model->setHeaders(headers);
  m_model->setElementHeader("Item");
  ui->treeView->setModel(m_model);
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

void MainWindow::onRemoveClicked() {
  auto parentIndex = ui->treeView->currentIndex().parent();
  int currentRow = ui->treeView->currentIndex().row();
  m_model->removeRow(currentRow, parentIndex);
}

void MainWindow::onUpClicked() {
  moveUp(ui->treeView->currentIndex());
}

void MainWindow::onDownClicked() {
  moveDown(ui->treeView->currentIndex());
}

bool MainWindow::moveDown(QModelIndex index) {
  QModelIndex parent = index.parent();
  QModelIndex newParent;
  int newRow = 0;
  if (index.row() == m_model->rowCount(parent) - 1) {
    if (!parent.isValid() ||
        parent.row() == m_model->rowCount(parent.parent()) - 1) {
      return false;
    }
    newParent = parent.siblingAtRow(parent.row() + 1);
    newRow = 0;
  } else {
    newParent = parent;
    newRow = index.row() + 1;
  }
  bool ok = m_model->moveRow(parent, index.row(), newParent, newRow);
  qDebug() << "Survived the move down";
  return ok;
}

bool MainWindow::moveUp(QModelIndex index) {
  QModelIndex parent = index.parent();
  QModelIndex newParent;
  int newRow = 0;
  if (index.row() == 0) {
    if (!parent.isValid() || parent.row() == 0) {
      return false;
    }
    newParent = parent.siblingAtRow(parent.row() - 1);
    newRow = m_model->rowCount(newParent);
  } else {
    newParent = parent;
    newRow = index.row() - 1;
  }
  bool ok = m_model->moveRow(parent, index.row(), newParent, newRow);
  qDebug() << "Survived the move up";
  return ok;
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::connectWithCore(AACore* mgr) {
  mgr->sayHello();
}
