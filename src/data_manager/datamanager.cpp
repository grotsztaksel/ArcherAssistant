#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
   ReturnCode r = tixiOpenDocument(xmlFilename, &handle);
   if (r != SUCCESS ){return;}
}
