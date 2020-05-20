#ifndef AASESSIONMANAGER_H
#define AASESSIONMANAGER_H

#include "aadirscanner.h"
#include "aaobject.h"

#include "aatreemodel.h"

class AASessionManager : public AAObject {
 public:
  explicit AASessionManager(AAObject* parent = nullptr,
                            const QStringList args = QStringList());

  void setDirScanner(AADirScanner* scanner);

 public slots:
  void setModel(AATreeModel* model);
  void updateSessions();

  AATreeNode_abstract* createNewSession(const QDateTime& dt);
  AATreeNode_abstract* createNewSeries(AATreeNode_abstract* session,
                                       const QDateTime& dt);

  AATreeNode_abstract* appendImage(AATreeNode_abstract* series,
                                   const QDateTime& dt,
                                   QString imageName);

 private:
  AATreeModel* m_model;
  AADirScanner* dirScanner;
  AATreeNode_abstract* m_sessionsNode;
};

#endif  // AASESSIONMANAGER_H
