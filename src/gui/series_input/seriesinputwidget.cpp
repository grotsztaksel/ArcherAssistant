#include "seriesinputwidget.h"
#include "seriesthumbnail.h"
#include "ui_seriesinputwidget.h"

#include <qdir.h>
#include <QDebug>
#include <QImageReader>
SeriesInputWidget::SeriesInputWidget(AATreeModel* model,
                                     AATreeNode_abstract* node,
                                     AAObject* settingsManager,
                                     QWidget* parent)
    : QWidget(parent),
      ui(new Ui::SeriesInputWidget),
      m_model{model},
      m_seriesNode{node},
      m_settingsMgr{settingsManager} {
  ui->setupUi(this);

  updateThumbnails();
  connect(ui->fitButton, SIGNAL(clicked()), ui->graphicsView, SLOT(fitView()));
  connect(ui->thumbnailsView, &QListWidget::itemClicked, this,
          &SeriesInputWidget::onImageSelected);
}

SeriesInputWidget::~SeriesInputWidget() {
  delete ui;
}

void SeriesInputWidget::updateThumbnails() {
  ui->thumbnailsView->clear();
  m_map.clear();
  QStringList paths;
  QFileInfoList fileInfos;

  for (AATreeNode_abstract* node : m_seriesNode->children("image")) {
    QString fileName(node->attribute("file").toString());
    QString dt(node->attribute("DateTime").toString());
    if (!QFile(fileName).exists()) {
      continue;
    }
    QImageReader reader(fileName);
    QListWidgetItem* thumb = new SeriesThumbnail(
        node, QIcon(QPixmap::fromImage(reader.read())), dt, ui->thumbnailsView);
    thumb->setToolTip(fileName);
    ui->thumbnailsView->addItem(thumb);
    m_map.insert(thumb, node);
  }
}

void SeriesInputWidget::onImageSelected(QListWidgetItem* item) {
  m_scene = new MainGraphicScene(this);
  ui->graphicsView->setScene(m_scene);

  connect(ui->graphicsView, SIGNAL(zoomed(qreal)), m_scene, SLOT(zoom(qreal)));

  m_scene->installEventFilter(ui->graphicsView);
  m_scene->setModel(m_model);

  QString path = item->toolTip();

  m_scene->switchImage(item);
  ui->graphicsView->fitView();
  currentImageNode = m_map.value(item);
}
