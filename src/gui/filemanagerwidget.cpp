#include "filemanagerwidget.h"
#include "aatreemodel.h"
#include "pathviewproxymodel.h"
#include "ui_filemanagerwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QImageReader>
#include <QMessageBox>
#include <QSet>

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
  ui->progressBar->hide();
}

FileManagerWidget::~FileManagerWidget() {
  delete ui;
}

void FileManagerWidget::connectFileManager(AAFileManager* fManager) {
  m_manager = fManager;

  // Connect signals and slots
  connect(ui->addPathButton, SIGNAL(clicked()), this,
          SLOT(onAddButtonClicked()));
  connect(ui->pathsListView->selectionModel(),
          SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
          SLOT(onSelectionChanged(QItemSelection, QItemSelection)));
  connect(ui->fileExtensionsLineEdit, SIGNAL(editingFinished()), this,
          SLOT(onEditingFinished()));

  ui->pathsListView->installEventFilter(this);
  ui->thumbnailsView->installEventFilter(this);
  ui->fileExtensionsLineEdit->setPlaceholderText(
      m_manager->getSetting(IMAGE_FILTER).toString());

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

void FileManagerWidget::updateLineEdit() {
  pathViewModel* proxyModel =
      qobject_cast<pathViewModel*>(ui->pathsListView->model());
  QList<QString> filters;
  for (QModelIndex index :
       ui->pathsListView->selectionModel()->selection().indexes()) {
    QModelIndex mIndex = proxyModel->mapToSource(index);
    auto node = m_manager->model()->nodeFromIndex(mIndex);

    QStringList pathFilters = node->attribute("filter").toString().split(
        QRegExp("; +"), QString::SkipEmptyParts);
    filters << pathFilters;
  }

  // Get rid of repeated filters
  filters = filters.toSet().toList();

  ui->fileExtensionsLineEdit->setText(filters.toSet().toList().join("; "));
}

void FileManagerWidget::updateThumbnails() {
  pathViewModel* proxyModel =
      qobject_cast<pathViewModel*>(ui->pathsListView->model());
  ui->thumbnailsView->clear();
  QStringList paths;
  QFileInfoList fileInfos;
  for (QModelIndex index :
       ui->pathsListView->selectionModel()->selection().indexes()) {
    QModelIndex mIndex = proxyModel->mapToSource(index);
    auto node = m_manager->model()->nodeFromIndex(mIndex);

    // Skip non existing directories
    QDir dir(node->attribute("dir").toString());
    if (!dir.exists()) {
      continue;
    }
    QString filter = node->attribute("filter").toString();
    if (filter.isEmpty()) {
      filter = m_manager->getSetting(IMAGE_FILTER).toString();
    }
    QStringList filters = filter.split(QRegExp("; +"));
    fileInfos << dir.entryInfoList(filters, QDir::Files, QDir::Time);
  }
  ui->progressBar->setMaximum(fileInfos.size());
  ui->progressBar->show();
  int i = 1;
  for (QFileInfo info : fileInfos) {
    QString path = info.filePath();
    QString name = info.fileName();
    ui->progressBar->setValue(i++);
    QImageReader reader(path);
    QListWidgetItem* thumb = new QListWidgetItem(
        QIcon(QPixmap::fromImage(reader.read())), name, ui->thumbnailsView);
    thumb->setToolTip(info.filePath());
    ui->thumbnailsView->addItem(thumb);
  }
  ui->progressBar->hide();
}

void FileManagerWidget::onEditingFinished() {
  QString filterValue = ui->fileExtensionsLineEdit->text();

  if (filterValue.startsWith("\u0010")) {
    filterValue = filterValue.mid(1);
  }

  pathViewModel* proxyModel =
      qobject_cast<pathViewModel*>(ui->pathsListView->model());
  for (QModelIndex index :
       ui->pathsListView->selectionModel()->selection().indexes()) {
    QModelIndex mIndex = proxyModel->mapToSource(index);
    auto node = m_manager->model()->nodeFromIndex(mIndex);
    qDebug() << "Editor gives" << filterValue;
    node->setAttribute("filter", filterValue);
  }
}

void FileManagerWidget::onAddButtonClicked() {
  QString newDir = QFileDialog::getExistingDirectory(
      this, tr("Add a data directory"), lastDir);

  m_manager->setPath(newDir);
}

void FileManagerWidget::onSelectionChanged(const QItemSelection& selected,
                                           const QItemSelection& deselected) {
  updateLineEdit();
  updateThumbnails();
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
  QItemSelection pathsSelected =
      ui->thumbnailsView->selectionModel()->selection();
  QModelIndexList indexes = pathsSelected.indexes();
  if (indexes.isEmpty()) {
    return;
  }
  auto ans = QMessageBox::question(this, "Remove images?",
                                   "Remove selected image paths from drive?");
  if (ans != QMessageBox::Yes) {
    return;
  }

  for (auto item : ui->thumbnailsView->selectedItems()) {
    QString fullPath = item->toolTip();
    QFile::remove(fullPath);
    ui->thumbnailsView->removeItemWidget(item);
  }
}
