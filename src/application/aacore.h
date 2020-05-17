#ifndef WORKER_H
#define WORKER_H

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QList>
#include <QSettings>
#include <QString>
#include <QTime>

#include "aaobject.h"

#include "aadirscanner.h"
#include "aasettingsmanager.h"
#include "datamanager.h"

#include <pugixml.hpp>

//! A central class governing interactions between all other classes
class AACore : public AAObject {
 public:
  explicit AACore(AAObject* parent = nullptr,
                  const QStringList args = QStringList());

  //! just a dummy function to see if the MainWindow object can communicate with
  //! this
  void sayHello();

  //! Function used byy other objects to query the core about the arguments
  //!
  QStringList getArgs() const;

  //! Return pointer to the main data model used
  //!
  AATreeModel* model() const;

 public slots:

 private:  // methods
  //! search the paths provided and find all the image files. Check the date of
  //! creation, and create a <series> node in <session> with date and times
  //! attributes.
  void updateSessions();

 private:  // variables
  AADirScanner* dirScanner = nullptr;
  AATreeModel* m_model = nullptr;

 signals:
};

#endif  // WORKER_H
