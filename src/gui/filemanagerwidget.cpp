#include "filemanagerwidget.h"
#include "aatreemodel.h"
#include "pathviewproxymodel.h"
#include "ui_filemanagerwidget.h"

#include <QDebug>

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
  //  ui->pathsListView->setModel(m_manager->model());

  updatePaths();
}

void FileManagerWidget::updatePaths() const {
  pathViewModel* proxyModel =
      qobject_cast<pathViewModel*>(ui->pathsListView->model());
  AATreeModel* model = m_manager->model();
  QModelIndex rootIndex = model->indexFromNode(m_manager->getNode());
  QModelIndex lastIndex;
  int rc = model->rowCount(rootIndex);
  if (rc > 0) {
    lastIndex = model->index(rc - 1, 0, rootIndex);
  } else {
    lastIndex = rootIndex;
  }
  proxyModel->setSourceModel(model);
  //  qDebug() << m_manager->model()->rowCount() << proxyModel->rowCount();
  ui->pathsListView->setRootIndex(proxyModel->mapFromSource(rootIndex));
  //  emit m_manager->model()->dataChanged(rootIndex, lastIndex);
  //  for (auto child : m_manager->getNode()->children("path")) {
  //    ui->pathsListView->addItem(child->attribute("dir").toString());
  //  }
}
