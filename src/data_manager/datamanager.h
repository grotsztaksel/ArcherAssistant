#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include "tixi.h"

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();

    void sayHello();
private:
    char* xmlFilename = "ju.xml";
    TixiDocumentHandle handle;

signals:


};

#endif // DATAMANAGER_H
