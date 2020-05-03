#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include "tixi.h"

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
private:
    char* xmlFilename = "ju.xml";
    TixiDocumentHandle handle = -1;

signals:


};

#endif // DATAMANAGER_H
