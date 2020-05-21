#include "filemanagerwidget.h"
#include "aatreemodel.h"
#include "ui_filemanagerwidget.h"

FileManagerWidget::FileManagerWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::FileManagerWidget) {
  ui->setupUi(this);
}

FileManagerWidget::~FileManagerWidget() {
  delete ui;
}

void FileManagerWidget::connectFileManager(AAFileManager* fManager) {
  m_manager = fManager;
  updatePaths();
}

void FileManagerWidget::updatePaths() const {
  for (auto child : m_manager->getNode()->children("path")) {
    ui->pathsListView->addItem(child->attribute("dir").toString());
  }
}
