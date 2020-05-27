#include "hourminsecwidget.h"
#include "ui_hourminsecwidget.h"

#include <limits.h>
HourMinSecWidget::HourMinSecWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::HourMinSecWidget) {
  ui->setupUi(this);

  ui->hours->setMaximum(INT_MAX / 3600 - 1);
  connect(ui->seconds, SIGNAL(valueChanged(int)), this,
          SLOT(onSecondsChanged(int)));
  connect(ui->minutes, SIGNAL(valueChanged(int)), this,
          SLOT(onMinutesChanged(int)));
  connect(ui->hours, SIGNAL(valueChanged(int)), this, SLOT(updateValue()));
}

HourMinSecWidget::~HourMinSecWidget() {
  delete ui;
}

void HourMinSecWidget::onSecondsChanged(int value) {
  blockSignals(true);
  if (value == 60) {
    ui->minutes->setValue(ui->minutes->value() + 1);
    ui->seconds->blockSignals(true);
    ui->seconds->setValue(0);
    ui->seconds->blockSignals(false);
  } else if (value == -1) {
    ui->minutes->setValue(ui->minutes->value() - 1);
    ui->seconds->blockSignals(true);
    ui->seconds->setValue(59);
    ui->seconds->blockSignals(false);
  }
  blockSignals(false);
  updateValue();
}

void HourMinSecWidget::onMinutesChanged(int value) {
  blockSignals(true);
  if (value == 60) {
    ui->hours->setValue(ui->minutes->value() + 1);
    ui->minutes->blockSignals(true);
    ui->minutes->setValue(0);
    ui->minutes->blockSignals(false);
  } else if (value == -1) {
    ui->hours->setValue(ui->minutes->value() - 1);
    ui->minutes->blockSignals(true);
    ui->minutes->setValue(59);
    ui->minutes->blockSignals(false);
  }
  blockSignals(false);
  updateValue();
}

qint64 HourMinSecWidget::totalSeconds() const {
  return hours() * 3600 + minutes() * 60 + seconds();
}

qint64 HourMinSecWidget::hours() const {
  return ui->hours->value();
}

qint64 HourMinSecWidget::minutes() const {
  return ui->minutes->value();
}

qint64 HourMinSecWidget::seconds() const {
  return ui->seconds->value();
}

void HourMinSecWidget::setValue(int value) {
  int lseconds_left;
  lseconds_left = value % 3600;
  int hours = value / 3600;
  value = lseconds_left;
  lseconds_left = value % 60;
  int minutes = value / 60;
  int seconds = lseconds_left;

  ui->hours->setValue(hours);
  ui->minutes->setValue(minutes);
  ui->seconds->setValue(seconds);
}

void HourMinSecWidget::updateValue() {
  int value = totalSeconds();
  emit valueChanged(value);
}
