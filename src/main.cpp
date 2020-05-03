#include "gui/mainwindow.h"
#include "datamanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataManager mgr;
    MainWindow w;
    w.connectDataManager(&mgr);
    w.show();
    return a.exec();
}
