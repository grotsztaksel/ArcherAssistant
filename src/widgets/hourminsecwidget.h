#ifndef HOURMINSECWIDGET_H
#define HOURMINSECWIDGET_H

#include <QWidget>

namespace Ui {
class HourMinSecWidget;
}

class HourMinSecWidget : public QWidget {
  Q_OBJECT
 signals:
  void valueChanged(qint64);

 public:
  explicit HourMinSecWidget(QWidget* parent = nullptr);
  ~HourMinSecWidget();

  qint64 totalSeconds() const;
  qint64 hours() const;
  qint64 minutes() const;
  qint64 seconds() const;

 public slots:
  void setValue(int value);
 private slots:
  void onSecondsChanged(int value);
  void onMinutesChanged(int value);
  void updateValue();

 private:
  Ui::HourMinSecWidget* ui;
};

#endif  // HOURMINSECWIDGET_H
