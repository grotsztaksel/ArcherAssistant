#include "aaobject.h"

#include <QDebug>
#include "aasettingsmanager.h"
AAObject::AAObject(QObject* parent, const QStringList& args)
    : QObject(parent),
      m_args{qobject_cast<AAObject*>(parent)
                 ? qobject_cast<AAObject*>(parent)->m_args
                 : args},
      gui{qobject_cast<AAObject*>(parent) ? qobject_cast<AAObject*>(parent)->gui
                                          : !args.contains(QString("--nogui"))},
      m_settings{qobject_cast<AAObject*>(parent)
                     ? qobject_cast<AAObject*>(parent)->m_settings
                     : nullptr}

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

QVariant AAObject::getSetting(const QString& settingName) const {
  AASettingsManager* s = qobject_cast<AASettingsManager*>(m_settings);
  return s->get(settingName);
}

AAObject* AAObject::getSettings() const {
  return m_settings;
}
