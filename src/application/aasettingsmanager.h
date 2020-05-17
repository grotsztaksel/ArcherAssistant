#ifndef AASETTINGSMANAGER_H
#define AASETTINGSMANAGER_H

#include <QObject>

#include <QSettings>
//! Class responsible for managing settings that can be saved between program
//! sessions
class AASettingsManager : public QObject {
  Q_OBJECT
 public:
  explicit AASettingsManager(const QStringList& args,
                             QObject* parent = nullptr);

  //! take the input argument xml="<filename>" and save it into the program
  //! settings. If the argument is not present, use the default one, saved in
  //! settings
  //!
  void setupConfigFile();

  //! set up default time intervals
  //!
  void setupIntervals();

  //! get the interval between sessions (in seconds). If the two images were
  //! created within interval shorter than this one (but longer than \ref
  //! seriesInterval seriesInterval()), they are considered to belong to the
  //! same session. Otherwise, finding an image created later triggers creation
  //! of a new session node
  //!
  qint64 getSessionInterval();

  //! \anchor seriesInterval get the difference between shooting series (in
  //! seconds). If the two images were created within interval shorter than this
  //! one, they are considered to document the same series (e.g photos taken
  //! from different angles, or lighting conditions to catch the locations of
  //! arrows better). Otherwise, finding an image created later triggers
  //! creation of a new series node
  //!
  qint64 getSeriesInterval();

 protected:
  //! create default settings, if they are absent
  //!
  void setUp();

 protected:
  //! program settings
  //!
  QSettings* settings = nullptr;

  //! list of input arguments passed from main as QStringList
  //!
  const QStringList args;
};

#endif  // AASETTINGSMANAGER_H
