#ifndef TRAININGSESSIONWINDOW_H
#define TRAININGSESSIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class TrainingSessionWindow;
}

class TrainingSessionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrainingSessionWindow(QWidget *parent = nullptr);
    ~TrainingSessionWindow();

private:
    Ui::TrainingSessionWindow *ui;
};

#endif // TRAININGSESSIONWINDOW_H
