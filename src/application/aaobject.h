#ifndef AAOBJECT_H
#define AAOBJECT_H

#include <QObject>
#include "settings.h"
//! Abstract class that all classes governed by the AACore should inherit from.
//! Defines set of common tools
class AAObject : public QObject {
  Q_OBJECT
 public:
  //! If the parent is of type AAObject, then:
  //!   - copies its CLI arguments
  //!   - keeps pointer to the settings object
  //! otherwise, it takes the arguments from the m_args.
  explicit AAObject(QObject* parent = nullptr,
                    const QStringList& m_args = QStringList());

 protected:
  //! Access the argument from args list, that starts with string arg. If the
  //! argument is exactly the arg (arg has been given), it returns this
  //! argument. If the argument has some value ('arg=val' syntax) - returns the
  //! value of the argument. Otherwise, returns an empty QString
  //!
  QString arg(const QString& arg);

  QVariant getSetting(const QString& settingName);

 protected:
  //! list of input arguments passed from main as QStringList
  //!
  const QStringList m_args;

  //! flag defining if the program was run with (true) or without (false) GUI.
  //!
  const bool gui;

  //! If the parent IS an AAObject and contains m_settings, it will pass it to
  //! this object.
  //!
  AAObject* m_settings = nullptr;
};

#endif  // AAOBJECT_H
