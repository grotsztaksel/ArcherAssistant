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

{}

void AACore::sayHello() {
  qDebug() << "Hello!@ The manager is reporting!";
}

QStringList AACore::getArgs() const {
  return args;
}
