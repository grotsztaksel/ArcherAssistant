#include "datamanager.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include "pugixml.hpp"

using namespace pugi;
DataManager::DataManager(QObject *parent) : QObject(parent)
{
}

DataManager::~DataManager()
{
        qDebug()<<"Destrouing Tixi:";
        //    tixiCloseDocument(handle);
}

void DataManager::sayHello()
{
    qDebug() << "Hello!@ The manager is reporting!";
}
