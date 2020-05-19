#ifndef AADIRSCANNER_H
#define AADIRSCANNER_H
#include "aaobject.h"
#include "aatreemodel.h"

//! A class responsible for images management. Among others, it's tasks include:
//! - scanning the database to recognize directories
//! - scanning directories to recognise available image files
//! - sorting the files by appropriate data (image creation date or file
//!   creation/modification date)
//!
class AADirScanner : public AAObject {
 public:
  explicit AADirScanner(AAObject* parent = nullptr,
                        const QStringList args = QStringList());

  //! Set the model to work with
  //!
  void setModel(AATreeModel* model);

 public slots:

  //! Set a path to look for images. if the path already available, ignore. If
  //! the path does not yet exist in the list, add it to the config file as well
  //!
  void setPath(const QString& path, AATreeNode_abstract* modelNode = nullptr);

  //! Call this function if the config file has been changed.
  //!
  void updateConfigFile();

  //! Scan the perviously set paths and find image files. Return them sorted by
  //! creation date/time taken either form EXIF metadata (if available), or by
  //! creation date/time taken from system
  //!
  void getImagesFiles();

 private:
  //! From the config file, read the <imagePath> nodes and, assuming that they
  //! define paths relative to the config file, find the paths
  //!
  void getPaths();

 private:
  //! Config model
  //!
  AATreeModel* m_model;

  //!  List of alrady known paths
  //!
  QStringList m_paths;

  //! Path tho the config file (without the filename itself)
  //!
  QString m_cfgPath;

  //! model node accessed by this class
  //!
  AATreeNode_abstract* m_imgNode = nullptr;
};

#endif  // AADIRSCANNER_H
