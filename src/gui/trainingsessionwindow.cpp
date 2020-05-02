#include "trainingsessionwindow.h"
#include "ui_trainingsessionwindow.h"

TrainingSessionWindow::TrainingSessionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrainingSessionWindow)
{
    ui->setupUi(this);
}

TrainingSessionWindow::~TrainingSessionWindow()
{
    delete ui;
}
