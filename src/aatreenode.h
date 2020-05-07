#ifndef SHOOTINGDATA_H
#define SHOOTINGDATA_H

#include <QDateTime>
#include <QList>
#include <QObject>

#include <pugixml.hpp>
class AATreeNode : public QObject {
  Q_OBJECT
 public:
  explicit AATreeNode(QString name = QString(),
                      AATreeNode* xmlParent = nullptr,
                      QObject* parent = nullptr);
  ~AATreeNode();

  QDate date();
  QTime time();
  QDateTime dateTime() const;

  //! Get type (name) of the element
  QString name();

  //! Get attribute of given type
  QVariant attribute(const QString name);

  //! check if the node has a given attribute
  bool hasAttribute(const QString name);

  //! set attribute of given name
  bool setAttribute(const QString name, const QVariant& value);

  //! clear attribute of given name
  bool removeAttribute(const QString name);
  //! Get list of all attributes
  QStringList attributes();

  //! Get list of direct children
  QList<AATreeNode*> children() const;

  //! Get the root node
  AATreeNode* root();

  void setDateTime(const QDateTime& dateTime);

 signals:

 protected:
  //! set the pugi pugi::xml_node object. Also, for each child detected in the
  //! pugi, create a representation of AATreeNode objects. This works
  //! recursively.
  void setXMLnode(pugi::xml_node node);

  //! helper function to quickly convert QString to char*
  const char* cstr(QString string);

 protected:
  QString m_name;
  pugi::xml_node m_xml_node;
  QDateTime m_dateTime;
  AATreeNode* m_parent = nullptr;
  QList<AATreeNode*> m_children;
  QHash<QString, QVariant> m_attributes;
};

#endif  // SHOOTINGDATA_H
