#include "aasessionmanager.h"
#include <QDebug>

#define PARENTNODE_SESSIONS "sessions"
#define DATE_FORMAT "yyyy.MM.dd HH:mm:ss"
AASessionManager::AASessionManager(AAObject* parent, const QStringList args)
    : AAObject(parent, args) {}

void AASessionManager::setModel(AATreeModel* model) {
  m_model = model;
  m_sessionsNode = m_model->root()->getChild(PARENTNODE_SESSIONS);
}

void AASessionManager::setDirScanner(AAFileManager* scanner) {
  dirScanner = scanner;
}

QDateTime AASessionManager::getDateTime(AATreeNode_abstract* node) const {
  return QDateTime ::fromString(node->attribute("DateTime").toString(),
                                DATE_FORMAT);
}

void AASessionManager::updateSessions(const QDateTime& from,
                                      const QDateTime& to) {
  // Get the file list
  QMap<QDateTime, QString> images = dirScanner->getImagesFiles();
  QMap<QDateTime, QString>::const_iterator i;
  QMap<QDateTime, QString>::const_iterator last;
  QDateTime previous;
  if (from.isValid()) {
    i = images.lowerBound(from);
    previous = from;
  } else {
    i = images.begin();
    previous = earliestDateTime();
  }

  if (to.isValid()) {
    last = images.upperBound(to);
  } else {
    last = images.end();
  }

  // Clear the nodes with datetime attributes from "from" to "to"
  QModelIndex firstToClear;
  int countToClear = 0;
  QModelIndex sessionsIndex = m_model->index(m_sessionsNode->getIndex(), 0);

  int insertAfter = -1;
  for (int i = 0; i < m_model->rowCount(sessionsIndex); i++) {
    QModelIndex sessionIndex = m_model->index(i, 0, sessionsIndex);
    AATreeNode_abstract* session = m_model->nodeFromIndex(sessionIndex);
    QDateTime dt = getDateTime(session);
    if (!firstToClear.isValid()) {
      if (dt >= from) {
        firstToClear = sessionIndex;
        countToClear++;
        continue;
      }
      insertAfter = i;
      continue;
    } else if (dt > to) {
      break;
    } else {
      countToClear++;
    }
  }

  if (countToClear > 0) {
    m_model->removeRows(firstToClear.row(), countToClear, sessionsIndex);
  }

  qint64 session_interval = getSetting(SESSION_INTVL).toInt();
  qint64 series_interval = getSetting(SERIES_INTVL).toInt();

  AATreeNode_abstract* series = nullptr;
  AATreeNode_abstract* session = nullptr;

  while (i != last) {
    auto key = i.key();
    ++i;
    if (previous.secsTo(key) >= session_interval) {
      session = createNewSession(insertAfter++, key);
      series = createNewSeries(session, key);
      previous = QDateTime(key);
    } else if (previous.secsTo(key) >= series_interval) {
      series = createNewSeries(session, key);
      previous = QDateTime(key);
    }
    appendImage(series, key, images.value(key));
  }
}

QDateTime AASessionManager::getLastResult() const {
  //    m_sessionsNode

  auto last = earliestDateTime();
  auto sessions = m_sessionsNode->children("session");
  if (sessions.isEmpty()) {
    return last;
  }
  auto isession = sessions.end();
  while (true) {
    isession--;
    AATreeNode_abstract* sessionNode = *isession;
    auto series = sessionNode->children("series");
    if (series.isEmpty()) {
      continue;
    }
    auto iseries = series.end();
    while (true) {
      iseries--;
      AATreeNode_abstract* seriesNode = *iseries;
      auto images = seriesNode->children("image");
      if (images.isEmpty()) {
        continue;
      }
      auto iimage = images.end();
      while (true) {
        iimage--;
        AATreeNode_abstract* imageNode = *iimage;
        QDateTime dt = getDateTime(imageNode);
        if (dt.isValid()) {
          return dt;
        }
        if (iimage == images.begin()) {
          break;
        }
      }
      // Maybe the series has DateTime attribute, but no images?
      QDateTime dt = getDateTime(seriesNode);
      if (dt.isValid()) {
        return dt;
      }
      if (iseries == series.begin()) {
        break;
      }
    }
    if (isession == sessions.begin()) {
      return last;
    }
  }
}

AATreeNode_abstract* AASessionManager::createNewSession(const int& after,
                                                        const QDateTime& dt) {
  QModelIndex index = m_model->indexFromNode(m_sessionsNode);
  QModelIndex sessionIndex =
      m_model->insertElement("session", index, after + 1);
  AATreeNode_abstract* newSession = m_model->nodeFromIndex(sessionIndex);

  newSession->setAttribute("DateTime", dt.toString(DATE_FORMAT));
  return newSession;
}

AATreeNode_abstract* AASessionManager::createNewSeries(
    AATreeNode_abstract* session,
    const QDateTime& dt) {
  QModelIndex index = m_model->indexFromNode(session);
  QModelIndex seriesIndex = m_model->insertElement("series", index);
  AATreeNode_abstract* newSeries = m_model->nodeFromIndex(seriesIndex);

  newSeries->setAttribute("DateTime", dt.toString(DATE_FORMAT));
  return newSeries;
}

AATreeNode_abstract* AASessionManager::appendImage(AATreeNode_abstract* series,
                                                   const QDateTime& dt,
                                                   QString imageName) {
  QModelIndex index = m_model->indexFromNode(series);
  QModelIndex imageIndex = m_model->insertElement("image", index);
  AATreeNode_abstract* image = m_model->nodeFromIndex(imageIndex);
  image->setAttribute("DateTime", dt.toString(DATE_FORMAT));
  image->setAttribute("file", imageName);
  return image;
}

QDateTime AASessionManager::earliestDateTime() const {
  QDateTime dt;
  dt.setMSecsSinceEpoch(0);
  return dt;
}
