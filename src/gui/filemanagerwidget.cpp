#include "filemanagerwidget.h"
#include "aatreemodel.h"
#include "pathviewproxymodel.h"
#include "ui_filemanagerwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *\
|                                                       |
|      The actual widget implementation                 |
|                                                       |
\*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

FileManagerWidget::FileManagerWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::FileManagerWidget) {
  ui->setupUi(this);

  auto pathProxyModel = new pathViewModel(this);
  ui->pathsListView->setModel(pathProxyModel);
}

FileManagerWidget::~FileManagerWidget() {
  delete ui;
}

void FileManagerWidget::connectFileManager(AAFileManager* fManager) {
  m_manager = fManager;

  connect(ui->addPathButton, SIGNAL(clicked()), this,
          SLOT(onAddButtonClicked()));

  QFileInfo cfgFileInfo(fManager->getSetting(CFG_FILE).toString());
  lastDir = cfgFileInfo.filePath();

  updatePaths();
}

void FileManagerWidget::updatePaths() const {
  pathViewModel* proxyModel =
      qobject_cast<pathViewModel*>(ui->pathsListView->model());
  AATreeModel* model = m_manager->model();
  QModelIndex rootIndex = m_manager->getNodeIndex();

  proxyModel->setSourceModel(model);

  ui->pathsListView->setRootIndex(proxyModel->mapFromSource(rootIndex));
}

void FileManagerWidget::updateLineEdit() {}

void FileManagerWidget::onAddButtonClicked() {
  QString newDir = QFileDialog::getExistingDirectory(
      this, tr("Add a data directory"), lastDir);

  m_manager->setPath(newDir);
}
