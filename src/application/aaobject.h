#ifndef AAOBJECT_H
#define AAOBJECT_H

#include <QObject>
//! Abstract class that all classes governed by the AACore should inherit from.
//! Defines set of common tools
class AAObject : public QObject {
  Q_OBJECT
 public:
  explicit AAObject(QObject* parent = nullptr,
                    const QStringList& m_args = QStringList());

 protected:
  //! Access the argument from args list, that starts with string arg. If the
  //! argument is exactly the arg (arg has been given), it returns this
  //! argument. If the argument has some value ('arg=val' syntax) - returns the
  //! value of the argument
  //!
  QString arg(const QString& arg);

 protected:
  //! list of input arguments passed from main as QStringList
  //!
  const QStringList m_args;

  //! flag defining if the program was run with (true) or without (false) GUI.
  //!
  const bool gui;
};

#endif  // AAOBJECT_H
