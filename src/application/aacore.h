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

struct config {};

class AACore : public QObject {
  Q_OBJECT
 public:
  explicit AACore(QObject* parent = nullptr,
                  const QStringList args = QStringList(),
                  const bool gui = true);

  //! just a dummy function to see if the MainWindow object can communicate with
  //! this
  void sayHello();
 public slots:

 private:  // methods
  //! create default settings, if they are absent
  void setUp();

  //! take the input argument xml="<filename>" and save it into the program
  //! settings. If the argument is not present, use the default one, saved in
  //! settings
  void setupConfigFile();

  //! set up default time intervals
  void setupIntervals();

  //! search the paths provided and find all the image files. Check the date of
  //! creation, and create a <series> node in <session> with date and times
  //! attributes.
  void updateSessions();

  //! get the interval between sessions (in seconds). If the two images were
  //! created within interval shorter than this one (but longer than \ref
  //! seriesInterval seriesInterval()), they are considered to belong to the
  //! same session. Otherwise, finding an image created later triggers creation
  //! of a new session node
  qint64 getSessionInterval();

  //! \anchor seriesInterval get the difference between shooting series (in
  //! seconds). If the two images were created within interval shorter than this
  //! one, they are considered to document the same series (e.g photos taken
  //! from different angles, or lighting conditions to catch the locations of
  //! arrows better). Otherwise, finding an image created later triggers
  //! creation of a new series node
  qint64 getSeriesInterval();

 private:  // variables
  //! list of input arguments passed from main as QStringList
  const QStringList args;
  //! flag defining if the program was run with (true) or without (false) GUI.
  const bool gui;
  //! program settings
  QSettings* settings = nullptr;

  //! the actual data structure collecting the QFile object and the pugi_xml
  //! object to work together
  DataManager data;

 signals:
};

#endif  // WORKER_H
