#ifndef WORKER_H
#define WORKER_H

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QList>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QTime>

#include "datamanager.h"

#include <pugixml.hpp>

//! A central class governing interactions between all other classes
class AACore : public QObject {
  Q_OBJECT
 public:
  explicit AACore(QObject* parent = nullptr,
                  const QStringList args = QStringList(),
                  const bool gui = true);

  //! just a dummy function to see if the MainWindow object can communicate with
  //! this
  void sayHello();

  //! Function used byy other objects to query the core about the arguments
  //!
  QStringList getArgs() const;

 public slots:

 private:  // methods
  //! search the paths provided and find all the image files. Check the date of
  //! creation, and create a <series> node in <session> with date and times
  //! attributes.
  void updateSessions();

 private:  // variables
  //! list of input arguments passed from main as QStringList
  //!
  const QStringList args;

  //! flag defining if the program was run with (true) or without (false) GUI.
  //!
  const bool gui;

  //! the actual data structure collecting the QFile object and the pugi_xml
  //! object to work together
  DataManager data;

 signals:
};

#endif  // WORKER_H
