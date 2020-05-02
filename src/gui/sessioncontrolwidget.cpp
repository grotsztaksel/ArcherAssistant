#include "sessioncontrolwidget.h"
#include "ui_sessioncontrolwidget.h"

SessionControlWidget::SessionControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionControlWidget)
{
    ui->setupUi(this);
}

SessionControlWidget::~SessionControlWidget()
{
    delete ui;
}
