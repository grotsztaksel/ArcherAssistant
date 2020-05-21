#include "aafilemanager.h"
#include <QDebug>
#include <QDir>
#include "exifreader.h"

#define ATTRIBUTE_DIR "dir"
#define NODE_PATH "path"
#define PARENTNODE_PATH "imagePaths"

AAFileManager::AAFileManager(AAObject* parent, const QStringList args)
    : AAObject(parent, args) {
  updateConfigFile();
}

void AAFileManager::setModel(AATreeModel* model) {
  m_model = model;
  m_imgNode = m_model->root()->getChild(PARENTNODE_PATH);
  getPaths();
}

void AAFileManager::setPath(const QString& path,
                            AATreeNode_abstract* modelNode) {
  AATreeNode_abstract* imgNode = m_model->root()->getChild(PARENTNODE_PATH);
  if (!m_paths.contains(path)) {
    m_paths.append(path);
    if (!imgNode->children().contains(modelNode)) {
      auto newPath = imgNode->addChild(NODE_PATH);
      newPath->setAttribute(ATTRIBUTE_DIR, path);
    }
  }
}

void AAFileManager::updateConfigFile() {
  QString cfgFile = getSetting(CFG_FILE).toString();
  m_cfgPath = QFileInfo(cfgFile).path();
}

QMap<QDateTime, QString> AAFileManager::getImagesFiles() {
  QFileInfoList fileInfos;
  QMap<QDateTime, QString> output;
  ExifReader er;
  for (QString path : m_paths) {
    QDir dir(path);
    fileInfos << dir.entryInfoList(getSetting(IMAGE_FILTER).toStringList(),
                                   QDir::Files, QDir::Time | QDir::Reversed);
  }
  for (QFileInfo finfo : fileInfos) {
    QFile file;
    file.setFileName(finfo.absoluteFilePath());
    bool ok = er.openFile(file);
    if (ok) {
      output.insert(er.originalDateTime(), file.fileName());
    }
  }
  return output;
}

QStringList AAFileManager::getPaths() const {
  return m_paths;
}

void AAFileManager::updatePaths() {
  for (auto child : m_imgNode->children(NODE_PATH)) {
    QDir imgDir(m_cfgPath + "/" + child->attribute(ATTRIBUTE_DIR).toString());
    if (imgDir.exists()) {
      setPath(imgDir.absolutePath(), child);
    }
  }
}

AATreeNode_abstract* AAFileManager::getNode() const {
  return m_imgNode;
}

// void AADirScanner::updateSessions() {
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
