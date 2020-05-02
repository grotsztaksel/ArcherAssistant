#ifndef SESSIONCONTROLWIDGET_H
#define SESSIONCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class SessionControlWidget;
}

class SessionControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SessionControlWidget(QWidget *parent = nullptr);
    ~SessionControlWidget();

private:
    Ui::SessionControlWidget *ui;
};

#endif // SESSIONCONTROLWIDGET_H
