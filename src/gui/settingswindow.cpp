#include "settingswindow.h"
#include "aasettingsmanager.h"
#include "ui_settingswindow.h"

#include <QDebug>
SettingsWindow::SettingsWindow(AASettingsManager* settings, QWidget* parent)
    : QDialog(parent), ui(new Ui::SettingsWindow), m_settings{settings} {
  ui->setupUi(this);

  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));

  ui->fileFilterEdit->setText(
      m_settings->get(IMAGE_FILTER).toStringList().join("; "));
  ui->seriesIntervalEdit->setValue(m_settings->get(SERIES_INTVL).toInt());
  ui->sessionIntervalEdit->setValue(m_settings->get(SESSION_INTVL).toInt());
}

SettingsWindow::~SettingsWindow() {
  delete ui;
}

void SettingsWindow::onAccepted() {
  QString filter = ui->fileFilterEdit->text();
  if (!filter.isEmpty()) {
    m_settings->set(IMAGE_FILTER, filter.split("; ", QString::SkipEmptyParts));
  }
  m_settings->set(SERIES_INTVL,
                  QVariant(ui->seriesIntervalEdit->totalSeconds()));
  m_settings->set(SESSION_INTVL,
                  QVariant(ui->sessionIntervalEdit->totalSeconds()));
}
