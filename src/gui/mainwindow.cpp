#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings *settings = new QSettings(QSettings::UserScope,"Home", "ArcherAssistant",this);
    if(settings->contains("configFile")){
        qDebug() <<"Config file in Window:"<<settings->value("configFile");
    }
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

void MainWindow::connectDataManager(Worker *mgr)
{
    mgr->sayHello();
}

