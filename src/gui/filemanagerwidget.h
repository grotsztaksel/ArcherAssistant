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

 public slots:

  //! Update the available paths from the model
  //!
  void updatePaths() const;

 private slots:
  //! If there is no selection, disable the line edit. Otherwise, display the
  //! filter string for the selected path. If more than one path is selected,
  //! combine their filters and display them, separated by semi-colons.
  //!
  void updateLineEdit();

  void onAddButtonClicked();

 private:
  Ui::FileManagerWidget* ui;

  //! Keep the last opened dir to make the further "Add directory" navigation
  //! easier. Start from the config file location
  //!
  QString lastDir;
  AAFileManager* m_manager;
};

#endif  // FILEMANAGERWIDGET_H
