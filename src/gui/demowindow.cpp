#include "demowindow.h"
#include <QDebug>
#include "stdio.h"
#include "ui_demowindow.h"
DemoWindow::DemoWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::DemoWindow) {
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

void DemoWindow::onLoadClicked() {
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
void DemoWindow::onSaveClicked() {
  QFile file;
  file.setFileName(
      "c:/Users/piotr/Documents/ArcherAssistant/raw_results/config_copy.xml");
  qDebug() << "Saving stuff";
  m_model->writeFile(file);
}

void DemoWindow::onAddClicked() {
  auto parentIndex = ui->treeView->currentIndex().parent();
  int currentRow = ui->treeView->currentIndex().row();
  m_model->insertElement("newItem", parentIndex, currentRow + 1);
}

void DemoWindow::onRemoveClicked() {
  auto parentIndex = ui->treeView->currentIndex().parent();
  int currentRow = ui->treeView->currentIndex().row();
  m_model->removeRow(currentRow, parentIndex);
}

void DemoWindow::onUpClicked() {
  moveUp(ui->treeView->currentIndex());
}

void DemoWindow::onDownClicked() {
  moveDown(ui->treeView->currentIndex());
}

bool DemoWindow::moveDown(QModelIndex index) {
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

bool DemoWindow::moveUp(QModelIndex index) {
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

DemoWindow::~DemoWindow() {
  delete ui;
}

void DemoWindow::connectWithCore(AACore* core) {
  auto headers = QStringList() << "name"
                               << "file"
                               << "DateTime"
                               << "diameter"
                               << "width";
  m_model = core->model();
  m_model->setHeaders(headers);
  m_model->setElementHeader("Item");
  ui->treeView->setModel(m_model);
}
