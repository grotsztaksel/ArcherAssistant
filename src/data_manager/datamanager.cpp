#include "datamanager.h"

#include <QDebug>
#include <QFileInfo>
using namespace pugi;
DataManager::DataManager(QObject* parent) : QObject(parent) {}

void DataManager::setBasicStructure() {
  root = pugi.document_element();
  if (QString(root.name()) != "ArcherAssistant") {
    root.set_name("ArcherAssistant");
    qDebug() << "Setting name";
    setModified();
  }
  xml_node sessions = root.child("sessions");
  if (sessions == nullptr) {
    root.append_child("sessions");
    qDebug() << "Adding sessions";
    setModified();
  }
}

DataManager::~DataManager() {
  if (opened && modified) {
    pugi.save_file(m_file->fileName().toStdString().c_str(), "  ");
    qDebug() << "Modified file" << m_file->fileName();
  }
}

void DataManager::setModified() {
  modified = true;
}

bool DataManager::isModified() const {
  return modified;
}

QFile* DataManager::file() const {
  return m_file;
}

QList<AATreeNode_abstract*> DataManager::getSessions() {
  QList<AATreeNode_abstract*> output;
  xml_node sessionsNode = root.child("sessions");
  for (xml_node session : sessionsNode.children("session")) {
  }
}

bool DataManager::openConfigFile(const QString& fileName) {
  if (m_file != nullptr) {
    m_file->deleteLater();
  }
  m_file = new QFile(fileName, this);
  opened = pugi.load_file(m_file->fileName().toStdString().c_str());
  if (opened)
    setBasicStructure();
  return opened;
}

QList<QDir> DataManager::getImagesPaths() {
  // Get the m_file's location (because paths may be relative)
  QFileInfo info = QFileInfo(*m_file);
  QDir xmlfileDir = info.path();
  QStringList relativePaths;
  QList<QDir> output;
  qDebug() << "Naa?";
  xml_node imagePathsNode = root.child("imagePaths");
  for (xml_node path : imagePathsNode.children("path")) {
    qDebug() << "OI";
    QString pathValue = QString(path.attribute("dir").value());
    QString absPath = xmlfileDir.absoluteFilePath(pathValue);
    QDir absDir = QDir(absPath);
    if (absDir.exists()) {
      output << absDir;
    } else {
      QDir absPath = QDir(pathValue);
      if (absPath.isAbsolute()) {
        output << absPath;
      }
    }
  }
  auto stuff = pugi.select_nodes("ArcherAssistant/sessions/session/series/hit");
  for (auto s : stuff) {
    qDebug() << "beep";
    qDebug() << QString::fromStdString(s.node().path());
  }
  return output;
}

void DataManager::getLastResult(QDateTime notYoungerThan) {
  QDateTime latest = QDateTime::fromString("1/01/1900", "d/MM/YYYY");
  if (!notYoungerThan.isValid()) {
    notYoungerThan = QDateTime::currentDateTime();
  }
  xml_node latestNode;
  auto sessions = pugi.select_nodes("/ArcherAssistant/sessions");

  for (auto session : sessions) {
    auto attribute = session.node().attribute("Date");
    if (!attribute)
      continue;
    QDate date =
        QDate::fromString(QString(session.node().attribute("Date").value()));
    QTime time =
        QTime::fromString(QString(session.node().attribute("Time").value()));
    QDateTime dt = QDateTime(date, time);
    if (!latest.isValid() || dt > latest) {
      latest = dt;
      latestNode = session.node();
    }
  }
  auto seriesSet = latestNode.children("series");
  for (auto series : seriesSet) {
    auto attribute = series.attribute("Date");
    if (!attribute)
      continue;
    QDate date = QDate::fromString(QString(series.attribute("Date").value()));
    QTime time = QTime::fromString(QString(series.attribute("Time").value()));
    QDateTime dt = QDateTime(date, time);
    if (dt > latest && dt <= notYoungerThan) {
      latest = dt;
      latestNode = series;
    }
  }
}
