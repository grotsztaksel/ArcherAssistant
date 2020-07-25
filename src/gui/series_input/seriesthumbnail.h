#ifndef SERIESTHUMBNAIL_H
#define SERIESTHUMBNAIL_H

#include <aatreenode_abstract.h>
#include <QListWidget>

class SeriesThumbnail : public QListWidgetItem {
 public:
  SeriesThumbnail(AATreeNode_abstract* imageNode,
                  const QIcon& icon,
                  const QString& text,
                  QListWidget* parent = nullptr,
                  int type = Type);

 private:
  AATreeNode_abstract* m_node;
};
#endif  // SERIESTHUMBNAIL_H
