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
    if (cfg.opened) {
        cfg.pugi.save_file(cfg.file->fileName().toStdString().c_str(), "  ");
    }
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

    QString filedir = QFileInfo(cfg.file->fileName()).absolutePath();
    auto imageAttr = cfg.pugi.document_element().child("sessions").attribute("imageDir");
    if (!imageAttr.empty()){
        filedir.append("/" + QString(imageAttr.value()));
    }
    return QDir(filedir);
}

bool DataManager::openConfigFile(){
    if (cfg.file != nullptr){
        cfg.file->deleteLater();
    }
    cfg.file = new QFile(settings->value("configFile").toString(), this);
    cfg.opened = cfg.pugi.load_file(cfg.file->fileName().toStdString().c_str());
    return cfg.opened;
}

void DataManager::updateSessions(){
    auto imageDir = this->getImagesPath();
    QFileInfoList fileInfos = imageDir.entryInfoList(settings->value("imagesFilter").toStringList(),QDir::Files);
    for (QFileInfo fileInfo : fileInfos){

    }
}
