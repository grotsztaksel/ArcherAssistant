#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onRunClicked()));
}

void MainWindow::onRunClicked(){
    tsWindow = new TrainingSessionWindow(this);
    tsWindow->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

