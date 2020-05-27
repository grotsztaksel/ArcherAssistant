#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <aasettingsmanager.h>
#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog {
  Q_OBJECT

 public:
  explicit SettingsWindow(AASettingsManager* settings,
                          QWidget* parent = nullptr);
  ~SettingsWindow();

 private slots:
  void onAccepted();

 private:
  Ui::SettingsWindow* ui;
  const AASettingsManager* m_settings;
};

#endif  // SETTINGSWINDOW_H
