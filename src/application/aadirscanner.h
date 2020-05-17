#ifndef AADIRSCANNER_H
#define AADIRSCANNER_H

#include <QObject>
#include "aatreemodel.h"

//! A class responsible for images management. Among others, it's tasks include:
//! - scanning the database to recognize directories
//! - scanning directories to recognise available image files
//! - sorting the files by appropriate data (image creation date or file
//!   creation/modification date)
//!
class AADirScanner : public QObject {
  Q_OBJECT
 public:
  explicit AADirScanner(QObject* parent = nullptr);

  //! Set the model to work with
  //!
  void setModel(AATreeModel* model);

 public slots:
  //! Set a path to look for images. if the path already available, ignore.
  //!
  void setPath(const QString& path);

 private:
  AATreeModel* m_model;
  QStringList m_paths;
};

#endif  // AADIRSCANNER_H
