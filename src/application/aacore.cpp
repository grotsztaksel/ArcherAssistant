#include "aacore.h"
#include <QDebug>
#include <QFileInfo>
#include "aatreenode_abstract.h"
#include "pugixml.hpp"
using namespace pugi;
AACore::AACore(AAObject* parent, const QStringList args)
    : AAObject(parent, args)

{
  m_settings = new AASettingsManager(this);
  m_fileManager = new AAFileManager(this);
  m_sessionManager = new AASessionManager(this);

  m_model = new AATreeModel(this);
  m_model->readFile(QFile(getSetting(CFG_FILE).toString()));

  m_fileManager->setModel(m_model);
  m_sessionManager->setModel(m_model);
  m_sessionManager->setDirScanner(m_fileManager);
  m_sessionManager->updateSessions();
}

void AACore::sayHello() {
  qDebug() << "Hello!@ The manager is reporting!";
}

AATreeModel* AACore::model() const {
  return m_model;
}

AAFileManager* AACore::fileManager() const {
  return m_fileManager;
}
