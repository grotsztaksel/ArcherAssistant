#include "filemanagerwindow.h"
#include "ui_filemanagerwindow.h"

FileManagerWindow::FileManagerWindow(QWidget* parent, AACore* core)
    : QDialog(parent),
      ui(new Ui::FileManagerWindow),
      m_fileManager{core->fileManager()} {
  ui->setupUi(this);
  ui->fmWidget->connectFileManager(m_fileManager);
}

FileManagerWindow::~FileManagerWindow() {
  delete ui;
}
