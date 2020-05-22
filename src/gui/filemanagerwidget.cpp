#include "filemanagerwidget.h"
#include "aatreemodel.h"
#include "pathviewproxymodel.h"
#include "ui_filemanagerwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

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

  ui->pathsListView->installEventFilter(this);
  ui->thumbnailsView->installEventFilter(this);

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

void FileManagerWidget::updateLineEdit(const QItemSelection& selected) {}

void FileManagerWidget::onAddButtonClicked() {
  QString newDir = QFileDialog::getExistingDirectory(
      this, tr("Add a data directory"), lastDir);

  m_manager->setPath(newDir);
}

void FileManagerWidget::onSelectionChanged(const QItemSelection& selected,
                                           const QItemSelection& deselected) {
  updateLineEdit(selected);
}

bool FileManagerWidget::eventFilter(QObject* obj, QEvent* event) {
  {
    if (event->type() == QEvent::KeyPress) {
      QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
      if (keyEvent->matches(QKeySequence::Delete)) {
        if (obj == ui->pathsListView) {
          deletePath();
        } else if (obj == ui->thumbnailsView) {
          deleteImages();
        } else {
          return false;
        }
        return true;
      }
    } else {
      // standard event processing
      return QObject::eventFilter(obj, event);
    }
  }
}

void FileManagerWidget::deletePath() {
  QItemSelection pathsSelected =
      ui->pathsListView->selectionModel()->selection();
  QModelIndexList indexes = pathsSelected.indexes();
  if (indexes.isEmpty()) {
    return;
  }

  auto ans = QMessageBox::question(
      this, "Remove path?", "Remove selected image paths from the database?");
  if (ans == QMessageBox::Yes) {
    pathViewModel* proxyModel =
        qobject_cast<pathViewModel*>(ui->pathsListView->model());
    for (auto index : indexes) {
      QModelIndex mIndex = proxyModel->mapToSource(index);
      m_manager->model()->removeRow(mIndex.row(), mIndex.parent());
    }
  }
}

void FileManagerWidget::deleteImages() {
  qDebug() << "WannaremovepIC";
}
