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
  if (m_paths.contains(path)) {
    return;
  }

  QModelIndex newIndex = m_model->insertElement(NODE_PATH, getNodeIndex());
  AATreeNode_abstract* newNode = m_model->nodeFromIndex(newIndex);
  newNode->setAttribute(ATTRIBUTE_DIR, path);

  m_paths.append(path);
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

QStringList AAFileManager::getPaths() {
  for (auto child : m_imgNode->children(NODE_PATH)) {
    QDir imgDir(child->attribute(ATTRIBUTE_DIR).toString());
    if (imgDir.exists()) {
      setPath(imgDir.absolutePath(), child);
    }
  }
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

AATreeModel* AAFileManager::model() const {
  return m_model;
}

AATreeNode_abstract* AAFileManager::getNode() const {
  return m_imgNode;
}

QString AAFileManager::getNodeName() {
  return QString(PARENTNODE_PATH);
}

QModelIndex AAFileManager::getNodeIndex() {
  return m_model->indexFromNode(m_imgNode);
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
