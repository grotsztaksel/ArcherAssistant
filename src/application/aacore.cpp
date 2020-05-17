#include "aacore.h"
#include <QDebug>
#include <QFileInfo>
#include "aatreenode_abstract.h"
#include "pugixml.hpp"
using namespace pugi;
AACore::AACore(AAObject* parent, const QStringList args)
    : AAObject(parent, args)

{
  dirScanner = new AADirScanner(this);
  settingsMgr = new AASettingsManager(this);
}

void AACore::sayHello() {
  qDebug() << "Hello!@ The manager is reporting!";
}
