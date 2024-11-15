#include "mainwindow.h"
#include "filemanagerwindow.h"
#include "seriesinputwidget.h"
#include "settingswindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle(programName);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::connectWithCore(AACore* core) {
  m_core = core;
  m_model = core->model();

  if (m_proxyModel) {
    m_proxyModel->deleteLater();
  }
  m_proxyModel = new SeriesInputProxyModel(this);
  m_proxyModel->setSourceModel(m_model);
  ui->treeView->setModel(m_proxyModel);
  //  qDebug() << ui->treeView->selectionModel();
  connect(ui->treeView->selectionModel(),
          SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
          SLOT(onSelectionChanged(QItemSelection, QItemSelection)));
  setWindowTitle(
      QString("%1 (%2)")
          .arg(programName)
          .arg(QDir::cleanPath(m_core->getSetting(CFG_FILE).toString())));
  setCentralWidget(new QWidget(this));
}

void MainWindow::onSelectionChanged(const QItemSelection& selected,
                                    const QItemSelection& deselected) {
  // Pass information to the scene, if one item is selected, and it is a series
  // or image

  if (selected.size() != 1) {
    return;
  }

  for (QModelIndex index : selected.indexes()) {
    QModelIndex srcIndex = m_proxyModel->mapToSource(index);
    auto node = m_model->nodeFromIndex(srcIndex);
    if (node->name() == "series") {
      setCentralWidget(new SeriesInputWidget(m_model, node,
                                             m_core->settingsManager(), this));
    }
  }
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

void MainWindow::on_actionProgram_settings_triggered() {
  SettingsWindow window(m_core->settingsManager(), this);
  window.exec();
}

void MainWindow::on_actionOpen_Project_triggered() {
  QString oldFileName = m_core->settingsManager()->get(CFG_FILE).toString();
  QStringList fileNames = QFileDialog::getOpenFileNames(
      this, "Select data file to open", oldFileName, "XML files (*.xml)");

  if (fileNames.isEmpty()) {
    return;
  }
  QString fileName = fileNames.at(0);
  m_core->settingsManager()->set(CFG_FILE, fileName);
  m_core->reset();
  connectWithCore(m_core);
}
