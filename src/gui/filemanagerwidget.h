#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <aacore.h>
#include <QWidget>

namespace Ui {
class FileManagerWidget;
}

class FileManagerWidget : public QWidget {
  Q_OBJECT

 public:
  explicit FileManagerWidget(QWidget* parent = nullptr);
  ~FileManagerWidget();

  void setCore(AACore* core);

  void connectFileManager(AAFileManager* fManager);

  void updatePaths() const;

 private:
  Ui::FileManagerWidget* ui;

  AAFileManager* m_manager;
};

#endif  // FILEMANAGERWIDGET_H
