#include "aasettingsmanager.h"

#include <QDebug>
#include <QFile>

AASettingsManager::AASettingsManager(AAObject* parent, const QStringList args)
    : AAObject(parent, args) {
  settings =
      new QSettings(QSettings::UserScope, "Home", "ArcherAssistant", this);
  setUp();
}

QVariant AASettingsManager::get(const QString& name) {
  if (settings->contains(name)) {
    return settings->value(name);
  }
  return QVariant();
}

void AASettingsManager::setUp() {
  setupConfigFile();
  setupIntervals();
}

void AASettingsManager::setupConfigFile(QString filename) {
  if (filename.isEmpty()) {
    for (QString arg : m_args) {
      if (arg.startsWith("cfg=")) {
        QString configFileName = arg.mid(4);
        if (QFile::exists(configFileName)) {
          settings->setValue(CFG_FILE, configFileName);
          break;
        }
      }
    }
  } else {
    settings->setValue(CFG_FILE, filename);
  }
  if (!settings->contains(CFG_FILE)) {
    settings->setValue(CFG_FILE, QString("config.xml"));
  }
}

void AASettingsManager::setupIntervals() {
  if (!settings->contains(SESSION_INTVL)) {
    qint64 sessionInterval = 60 * 20;  // 60 sec times minutes
    settings->setValue(SESSION_INTVL, sessionInterval);
  }
  if (!settings->contains(SERIES_INTVL)) {
    qint64 seriesInterval = 60 * 2;  // 60 sec times minutes
    settings->setValue(SERIES_INTVL, seriesInterval);
  }
}

void AASettingsManager::setupImageFIleExtensions() {
  if (!settings->contains(IMAGE_FILTER)) {
    settings->setValue(IMAGE_FILTER, QStringList() << "*.jpg"
                                                   << "*.png");
  }
}

qint64 AASettingsManager::getSessionInterval() {
  return settings->value(SERIES_INTVL).toInt();
}

qint64 AASettingsManager::getSeriesInterval() {
  return settings->value(SERIES_INTVL).toInt();
}
