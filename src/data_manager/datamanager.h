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

  //! Pointer to the QFile object
  QFile* file = nullptr;
  //! The actual XML data structure
  pugi::xml_document pugi;
  //! Root node, for more convenient navigation

  //! Flag informing if the file has been opened
  bool opened = false;
  //! Flag informing, if the file has been modified
  bool modified = false;

  //! Create the basic structure of the config tree. If the structure,
  //! or its parts are already present, keep them
  void setBasicStructure();

 public slots:
  //! Convinience function to set the modified flag to true
  bool openConfigFile(const QString& fileName);
  //! Scan the config file to return the default paths where the images should
  //! be sought for
  QList<QDir> getImagesPaths();

 private:
  void setModified();

 private:
  pugi::xml_node root;
 signals:
};

#endif  // DATAMANAGER_H
