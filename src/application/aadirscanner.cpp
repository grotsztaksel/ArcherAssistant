#include "aadirscanner.h"
#include <QDebug>

AADirScanner::AADirScanner(AAObject* parent, const QStringList args)
    : AAObject(parent, args) {}

void AADirScanner::setModel(AATreeModel* model) {
  m_model = model;
}

void AADirScanner::setPath(const QString& path) {
  if (!m_paths.contains(path)) {
    m_paths.append(path);
  }
}

/*
void AADirScanner::updateSessions() {
  auto imageDir = data.getImagesPaths();
  QFileInfoList fileInfos;
  // get the list of inage files, sorted by creation time
  for (QDir imageDir : data.getImagesPaths()) {
    qDebug() << "Dir found: " << imageDir.absolutePath();
    //    fileInfos << imageDir.entryInfoList(
    //        settings->value("imagesFilter").toStringList(), QDir::Files,
    //        QDir::Time | QDir::Reversed);
  }
  for (auto finfo : fileInfos) {
    qDebug() << finfo.filePath()
             << finfo.fileTime(QFileDevice::FileMetadataChangeTime);
  }

  QDateTime lastResult;  // = data.getLastResult();
  qDebug() << lastResult;

  if (lastResult.isValid()) {
    for (auto finfo : fileInfos) {
      if (finfo.fileTime(QFileDevice::FileMetadataChangeTime) < lastResult) {
        fileInfos.removeOne(finfo);
      } else {
        break;  // Assuming the files were sorted by their creation date, there
                // is no need to scan the remaining files
      }
    }
  }

  //  qint64 sessionInterval = getSessionInterval();
  //  qint64 seriesInterval = getSessionInterval();

  // go to the last save session/series to get the date
}
//    xml_node lastSeries =
//
cfg.pugi.document_element().child("sessions").last_child("session").last_child("series");
//    if (lastSeries.empty()){
//        //create the
//    }
//    for (QFileInfo fileInfo : fileInfos){
//    }
*/
