#ifndef AAFILEMANAGER_H
#define AAFILEMANAGER_H
#include "aaobject.h"
#include "aatreemodel.h"

//! A class responsible for images management. Among others, it's tasks include:
//! - scanning the database to recognize directories
//! - scanning directories to recognise available image files
//! - sorting the files by appropriate data (image creation date or file
//!   creation/modification date)
//!
class AAFileManager : public AAObject {
 public:
  explicit AAFileManager(AAObject* parent = nullptr,
                         const QStringList args = QStringList());

  //! Set the model to work with
  //!
  void setModel(AATreeModel* model);

  //! Access the model
  //!
  AATreeModel* model() const;

  //! Return the list of saved paths
  //!
  QStringList getPaths() const;

  //! Access the node handled by this manager
  //!
  AATreeNode_abstract* getNode() const;

  //! Get the name of the node handled by this manager
  //!
  static QString getNodeName();

  //! Get the name of the node handled by this manager
  //!
  QModelIndex getNodeIndex();

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
  QMap<QDateTime, QString> getImagesFiles();

 private:
  //! From the config file, read the <imagePath> nodes and, assuming that they
  //! define paths relative to the config file, find the paths
  //!
  void updatePaths();

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

#endif  // AAFILEMANAGER_H
