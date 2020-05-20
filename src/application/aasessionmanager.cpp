#include "aasessionmanager.h"
#include <QDebug>

#define PARENTNODE_SESSIONS "sessions"
AASessionManager::AASessionManager(AAObject* parent, const QStringList args)
    : AAObject(parent, args) {}

void AASessionManager::setModel(AATreeModel* model) {
  m_model = model;
  m_sessionsNode = m_model->root()->getChild(PARENTNODE_SESSIONS);
}

void AASessionManager::setDirScanner(AADirScanner* scanner) {
  dirScanner = scanner;
}

void AASessionManager::updateSessions() {
  // Clear the node first
  QModelIndex index = m_model->index(m_sessionsNode->getIndex(), 0);
  m_model->removeRows(0, m_model->rowCount(index), index);
  // Get the file list
  QMap<QDateTime, QString> images = dirScanner->getImagesFiles();

  QDateTime previous;
  previous.setMSecsSinceEpoch(0);

  qint64 session_interval = getSetting(SESSION_INTVL).toInt();
  qint64 series_interval = getSetting(SERIES_INTVL).toInt();

  AATreeNode_abstract* series = nullptr;
  AATreeNode_abstract* session = nullptr;

  for (QDateTime key : images.keys()) {
    if (previous.secsTo(key) >= session_interval) {
      session = createNewSession(key);
      series = createNewSeries(session, key);
      previous = QDateTime(key);
    } else if (previous.secsTo(key) >= series_interval) {
      series = createNewSeries(session, key);
      previous = QDateTime(key);
    }
    appendImage(series, key, images.value(key));
  }
}

AATreeNode_abstract* AASessionManager::createNewSession(const QDateTime& dt) {
  QModelIndex index = m_model->indexFromNode(m_sessionsNode);
  QModelIndex sessionIndex = m_model->insertElement("session", index);
  AATreeNode_abstract* newSession = m_model->nodeFromIndex(sessionIndex);

  newSession->setAttribute("DateTime", dt.toString("yyyy.MM.dd HH:mm"));
  return newSession;
}

AATreeNode_abstract* AASessionManager::createNewSeries(
    AATreeNode_abstract* session,
    const QDateTime& dt) {
  QModelIndex index = m_model->indexFromNode(session);
  QModelIndex seriesIndex = m_model->insertElement("series", index);
  AATreeNode_abstract* newSeries = m_model->nodeFromIndex(seriesIndex);

  newSeries->setAttribute("DateTime", dt.toString("yyyy.MM.dd HH:mm"));
  return newSeries;
}

AATreeNode_abstract* AASessionManager::appendImage(AATreeNode_abstract* series,
                                                   const QDateTime& dt,
                                                   QString imageName) {
  QModelIndex index = m_model->indexFromNode(series);
  QModelIndex imageIndex = m_model->insertElement("image", index);
  AATreeNode_abstract* image = m_model->nodeFromIndex(imageIndex);
  image->setAttribute("DateTime", dt.toString("yyyy.MM.dd HH:mm"));
  image->setAttribute("file", imageName);
  return image;
}

// void AASessionManager::updateSessions() {
//  auto imageDir = data.getImagesPaths();
//  QFileInfoList fileInfos;
//  // get the list of inage files, sorted by creation time
//  for (QDir imageDir : data.getImagesPaths()) {
//    qDebug() << "Dir found: " << imageDir.absolutePath();
//    fileInfos << imageDir.entryInfoList(
//        settings->value("imagesFilter").toStringList(), QDir::Files,
//        QDir::Time | QDir::Reversed);
//  }
//  for (auto finfo : fileInfos) {
//    qDebug() << finfo.filePath()
//             << finfo.fileTime(QFileDevice::FileMetadataChangeTime);
//  }

//  QDateTime lastResult;  // = data.getLastResult();
//  qDebug() << lastResult;

//  if (lastResult.isValid()) {
//    for (auto finfo : fileInfos) {
//      if (finfo.fileTime(QFileDevice::FileMetadataChangeTime) < lastResult) {
//        fileInfos.removeOne(finfo);
//      } else {
//        break;  // Assuming the files were sorted by their creation date,
//        there
//                // is no need to scan the remaining files
//      }
//    }
//  }
//}
