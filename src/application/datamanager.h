#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QTime>

#include <pugixml.hpp>
#include "aatreenode_abstract.h"
//! DataManager does the following:
//! - Keep the access to the config XML file
//! - Keep the internal XML structure based on an XML library
//! - Perform operations on this structure on request from other classes
class DataManager : public QObject {
  Q_OBJECT
 public:
  explicit DataManager(QObject* parent = nullptr);

  //! When save the file if it has been modified
  ~DataManager();

  //! Create the basic structure of the config tree. If the structure,
  //! or its parts are already present, keep them
  void setBasicStructure();

  //! Get QFile object associated with the xml data file
  QFile* file() const;

  //! Return list of pointers to the Session objects
  QList<AATreeNode_abstract*> getSessions();
  //! Return list of pointers to the Series objects of a given session
  QList<AATreeNode_abstract*> getSeries(const AATreeNode_abstract* session);
  //! Return list of pointers to the Shot objects of a given series
  QList<AATreeNode_abstract*> getShots(const AATreeNode_abstract* series);
  //! Add a session
  AATreeNode_abstract* addSession(int index = -1);
  //! Add a Series to a given session
  AATreeNode_abstract* addSeries(const AATreeNode_abstract* session,
                                 int index = -1);
  //! Add a shot to a given series
  AATreeNode_abstract* addShot(const AATreeNode_abstract* series,
                               int index = -1);

  bool removeSession(int index = -1);
  bool removeSeries(const AATreeNode_abstract* session, int index = -1);

  bool isModified() const;

 public slots:
  //! Convinience function to set the modified flag to true
  bool openConfigFile(const QString& fileName);

  //! Scan the config file to return the default paths where the images should
  //! be sought for
  QList<QDir> getImagesPaths();

  //! Return the latest result (session, if empty, or series) that is older than
  //! given date.
  void getLastResult(QDateTime notYOungerThan = QDateTime());
  //  void getSeriesByImagePath(const QString& imageFile);

 private:
  void setModified();

 private:
  //! Root node, for more convenient navigation
  pugi::xml_node root;
  //! Flag informing if the file has been opened
  bool opened = false;
  //! Flag informing, if the file has been modified
  bool modified = false;
  //! The actual XML data structure
  pugi::xml_document pugi;
  //! Pointer to the QFile object
  QFile* m_file = nullptr;

 signals:
};

#endif  // DATAMANAGER_H
