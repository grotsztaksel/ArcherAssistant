#include "aacore.h"
#include <QDebug>
#include <QFileInfo>
#include "aatreenode_abstract.h"
#include "pugixml.hpp"
using namespace pugi;
AACore::AACore(QObject* parent, const QStringList args, const bool gui)
    : QObject(parent),
      args{args},
      gui{gui}  // used gui{gui} in member initializer lists, even though it is
                // still in the args - because gui is const
{
  settings =
      new QSettings(QSettings::UserScope, "Home", "ArcherAssistant", this);
  setUp();
  data.openConfigFile(settings->value("configFile").toString());
  qDebug() << QDateTime::currentDateTime().toString();
  qDebug() << QDateTime::currentDateTime().date().toString("dd.MM.yyyy");
  qDebug() << QDateTime::currentDateTime().time().toString("HH:mm:ss");

  updateSessions();
}

void AACore::setUp() {
  setupConfigFile();
  setupIntervals();
}

void AACore::setupConfigFile() {
  for (QString arg : args) {
    if (arg.startsWith("cfg=")) {
      QString configFileName = arg.mid(4);
      if (QFile::exists(configFileName)) {
        settings->setValue("configFile", configFileName);
        break;
      }
    }
  }
  if (!settings->contains("configFile")) {
    qDebug() << "setting configFile";
    settings->setValue("configFile", QString("config.xml"));
  }
}

void AACore::setupIntervals() {
  if (!settings->contains("sessionInterval")) {
    qint64 sessionInterval = 60 * 20;  // 60 sec times minutes
    settings->setValue("sessionInterval", sessionInterval);
  }
  if (!settings->contains("seriesInterval")) {
    qint64 seriesInterval = 60 * 4;  // 60 sec times minutes
    settings->setValue("seriesInterval", seriesInterval);
  }
}

void AACore::sayHello() {
  qDebug() << "Hello!@ The manager is reporting!";
}

void AACore::updateSessions() {
  auto imageDir = data.getImagesPaths();
  QFileInfoList fileInfos;
  // get the list of inage files, sorted by creation time
  for (QDir imageDir : data.getImagesPaths()) {
    qDebug() << "Dir found: " << imageDir.absolutePath();
    fileInfos << imageDir.entryInfoList(
        settings->value("imagesFilter").toStringList(), QDir::Files,
        QDir::Time | QDir::Reversed);
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

  qint64 sessionInterval = getSessionInterval();
  qint64 seriesInterval = getSessionInterval();

  // go to the last save session/series to get the date
}
//    xml_node lastSeries =
//    cfg.pugi.document_element().child("sessions").last_child("session").last_child("series");
//    if (lastSeries.empty()){
//        //create the
//    }
//    for (QFileInfo fileInfo : fileInfos){
//    }

qint64 AACore::getSessionInterval() {
  return settings->value("sessionInterval").toInt();
}

qint64 AACore::getSeriesInterval() {
  return settings->value("seriesInterval").toInt();
}
