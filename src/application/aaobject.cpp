#include "aaobject.h"

#include <QDebug>
AAObject::AAObject(QObject* parent, const QStringList& args)
    : QObject(parent),
      m_args{qobject_cast<AAObject*>(parent)
                 ? qobject_cast<AAObject*>(parent)->m_args
                 : args},
      gui{qobject_cast<AAObject*>(parent) ? qobject_cast<AAObject*>(parent)->gui
                                          : !args.contains(QString("--nogui"))}
// Initialize the object with parent's values of gui and m_args IF the parent is
// an AAObject. Otherwise use the values from arguments
{}

QString AAObject::arg(const QString& arg) {
  if (m_args.contains(arg))
    return arg;

  for (QString arg_ : m_args) {
    if (arg_.startsWith(arg + "=")) {
      return arg_.section("=", 1);
    }
  }
  return QString();
}
