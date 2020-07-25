#include "seriesthumbnail.h"

SeriesThumbnail::SeriesThumbnail(AATreeNode_abstract* imageNode,
                                 const QIcon& icon,
                                 const QString& text,
                                 QListWidget* parent,
                                 int type)
    : QListWidgetItem(icon, text, parent, type), m_node{imageNode} {}
