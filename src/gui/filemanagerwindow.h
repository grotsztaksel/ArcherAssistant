#ifndef FILEMANAGERWINDOW_H
#define FILEMANAGERWINDOW_H

#include <aacore.h>
#include <QDialog>

namespace Ui {
class FileManagerWindow;
}

class FileManagerWindow : public QDialog {
  Q_OBJECT

 public:
  explicit FileManagerWindow(QWidget* parent = nullptr, AACore* core = nullptr);
  ~FileManagerWindow();

 private:
  Ui::FileManagerWindow* ui;
  AAFileManager* m_fileManager = nullptr;
};

#endif  // FILEMANAGERWINDOW_H
