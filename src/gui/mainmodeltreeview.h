#ifndef MAINMODELTREEVIEW_H
#define MAINMODELTREEVIEW_H

#include <QTreeView>

// ! A dedicated class for the main tree view.
class MainModelTreeView : public QTreeView {
  Q_OBJECT
 public:
  explicit MainModelTreeView(QWidget* parent = nullptr);

 signals:
};

#endif  // MAINMODELTREEVIEW_H
