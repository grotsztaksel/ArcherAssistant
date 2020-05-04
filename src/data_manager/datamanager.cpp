#include "datamanager.h"
#include <QDebug>
#include <QFileInfo>
#include "pugixml.hpp"


DataManager::DataManager(QObject *parent, const QStringList args, const bool gui) : QObject(parent), args{args}, gui{gui}
{
    settings = new QSettings(QSettings::UserScope,"Home", "ArcherAssistant",this);

    // check if the args contain the config file

    for (QString arg: args){
        if (arg.startsWith("cfg=")) {
            QString configFileName = arg.mid(4);
            if (QFile::exists(configFileName)){
                settings->setValue("configFile", configFileName);
                break;
            }
        }
    }

    if (!settings->contains("configFile")){
        settings->setValue("configFile", QString("config.xml"));
    }
    if (!gui){
        qDebug()<< "No window!";
    }
    configFile = new QFile(settings->value("configFile").toString(), this);
    auto result = config.load_file(configFile->fileName().toStdString().c_str());

}

DataManager::~DataManager()
{
    auto fileName = settings->value("configFile").toString().toStdString().c_str();
    config.save_file(fileName);    
}

void DataManager::sayHello()
{
    qDebug() << "Hello!@ The manager is reporting!";
}

QDir DataManager::getImagesPath(){

    QString filedir = QFileInfo(configFile->fileName()).absolutePath();
    auto imageAttr = config.document_element().child("sessions").attribute("imageDir");
    if (!imageAttr.empty()){
        filedir.append("/" + QString(imageAttr.value()));
    }
    return QDir(filedir);
}

void DataManager::updateSessions(){
    auto imageDir = this->getImagesPath();
    QFileInfoList fileInfos = imageDir.entryInfoList(settings->value("imagesFilter").toStringList(),QDir::Files);
    for (QFileInfo fileInfo : fileInfos){

    }
}
