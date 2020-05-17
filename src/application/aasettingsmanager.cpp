#include "aasettingsmanager.h"

#include <QDebug>
#include <QFile>

AASettingsManager::AASettingsManager(const QStringList& args, QObject* parent)
    : QObject(parent), args{args} {
  settings =
      new QSettings(QSettings::UserScope, "Home", "ArcherAssistant", this);
  setUp();
}

void AASettingsManager::setUp() {
  setupConfigFile();
  setupIntervals();
}

void AASettingsManager::setupConfigFile() {
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

void AASettingsManager::setupIntervals() {
  if (!settings->contains("sessionInterval")) {
    qint64 sessionInterval = 60 * 20;  // 60 sec times minutes
    settings->setValue("sessionInterval", sessionInterval);
  }
  if (!settings->contains("seriesInterval")) {
    qint64 seriesInterval = 60 * 4;  // 60 sec times minutes
    settings->setValue("seriesInterval", seriesInterval);
  }
}

qint64 AASettingsManager::getSessionInterval() {
  return settings->value("sessionInterval").toInt();
}

qint64 AASettingsManager::getSeriesInterval() {
  return settings->value("seriesInterval").toInt();
}
