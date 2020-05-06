#include "gui/mainwindow.h"
#include "worker.h"

#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Translate the argv to QStringList
    QStringList args = QStringList();
    for (int i = 0; i < argc; i++){
        args << QString(argv[i]);
    }
    bool gui = !args.contains(QString("--nogui"));
    qDebug() << "Creating window? "<<gui;
    Worker mgr(nullptr, args, gui);

    // Allow the DataManager to work alone, without GUI (batch mode)
    if (gui){
        qDebug() << "Creating window";
        MainWindow w;
        w.connectDataManager(&mgr);
        w.show();
        return a.exec();
    } else {
        return 0;
    }

}
