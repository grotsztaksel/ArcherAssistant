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
  dirScanner = new AADirScanner(this);
  m_sessionManager = new AASessionManager(this);

  m_model = new AATreeModel(this);
  m_model->readFile(QFile(getSetting(CFG_FILE).toString()));

  dirScanner->setModel(m_model);
  m_sessionManager->setModel(m_model);
  m_sessionManager->setDirScanner(dirScanner);
  m_sessionManager->updateSessions();
}

void AACore::sayHello() {
  qDebug() << "Hello!@ The manager is reporting!";
}

AATreeModel* AACore::model() const {
  return m_model;
}
