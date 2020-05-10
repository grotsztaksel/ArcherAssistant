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
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onRunClicked()));
}

void MainWindow::onRunClicked() {
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

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::connectDataManager(Worker* mgr) {
  mgr->sayHello();
}
