#include "aacore.h"
#include "gui/demowindow.h"

#include <QApplication>

#include <QDebug>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // Translate the argv to QStringList
  QStringList args = QStringList();
  for (int i = 0; i < argc; i++) {
    args << QString(argv[i]);
  }
  bool gui = !args.contains(QString("--nogui"));
  AACore core(nullptr, args);

  // Allow the DataManager to work alone, without GUI (batch mode)
  if (gui) {
    DemoWindow w;
    w.connectWithCore(&core);
    w.show();
    return a.exec();
  } else {
    return 0;
  }
}
