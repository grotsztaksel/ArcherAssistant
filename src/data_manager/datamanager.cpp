#include "datamanager.h"
#include <QDebug>
#include <QFileInfo>
#include "pugixml.hpp"



DataManager::DataManager(QObject *parent, const QStringList args, const bool gui) : QObject(parent), args{args}, gui{gui}
// used gui{gui} in member initializer lists, even though it is still in the args - because gui is const
{
    settings = new QSettings(QSettings::UserScope,"Home", "ArcherAssistant",this);

    // check if the args contain the config file
    setupConfigFile();
}

DataManager::~DataManager()
{
    auto fileName = settings->value("configFile").toString().toStdString().c_str();
    config.save_file(fileName);    
}

void DataManager::setupConfigFile()
{
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

bool DataManager::openConfigFile(){
    if (configFile != nullptr){
        configFile->deleteLater();
    }
    configFile = new QFile(settings->value("configFile").toString(), this);
    return config.load_file(configFile->fileName().toStdString().c_str());

}

void DataManager::updateSessions(){
    auto imageDir = this->getImagesPath();
    QFileInfoList fileInfos = imageDir.entryInfoList(settings->value("imagesFilter").toStringList(),QDir::Files);
    for (QFileInfo fileInfo : fileInfos){

    }
}
