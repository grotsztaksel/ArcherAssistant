#ifndef AASESSIONMANAGER_H
#define AASESSIONMANAGER_H

#include "aafilemanager.h"
#include "aaobject.h"

#include "aatreemodel.h"

class AASessionManager : public AAObject {
 public:
  explicit AASessionManager(AAObject* parent = nullptr,
                            const QStringList args = QStringList());

  void setDirScanner(AAFileManager* scanner);

  QDateTime getDateTime(AATreeNode_abstract* node) const;

 public slots:
  void setModel(AATreeModel* model);
  void updateSessions(const QDateTime& from = QDateTime(),
                      const QDateTime& to = QDateTime());

  QDateTime getLastResult() const;
  AATreeNode_abstract* createNewSession(const int& after, const QDateTime& dt);
  AATreeNode_abstract* createNewSeries(AATreeNode_abstract* session,
                                       const QDateTime& dt);

  AATreeNode_abstract* appendImage(AATreeNode_abstract* series,
                                   const QDateTime& dt,
                                   QString imageName);

 private:
  QDateTime earliestDateTime() const;

 private:
  AATreeModel* m_model;
  AAFileManager* dirScanner;
  AATreeNode_abstract* m_sessionsNode;
};

#endif  // AASESSIONMANAGER_H
