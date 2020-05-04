#include "datamanager.h"
#include <QDebug>
#include <QFileInfo>
#include "pugixml.hpp"


using namespace pugi;
DataManager::DataManager(QObject *parent, const QStringList args, const bool gui) : QObject(parent), args{args}, gui{gui}
// used gui{gui} in member initializer lists, even though it is still in the args - because gui is const
{
    settings = new QSettings(QSettings::UserScope,"Home", "ArcherAssistant",this);
    setUp();
    openConfigFile();
}

DataManager::~DataManager()
{
    if (cfg.opened && cfg.modified) {
        cfg.pugi.save_file(cfg.file->fileName().toStdString().c_str(), "  ");
        qDebug() << "Modified file"<<cfg.file->fileName();
    }
}

void DataManager::setUp()
{
    setupConfigFile();
    setupIntervals();
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
        qDebug()<<"setting configFile";
        settings->setValue("configFile", QString("config.xml"));
    }
}

void DataManager::setupIntervals(){
    if (!settings->contains("sessionInterval")){
        qint64 sessionInterval = 60 * 20; // 60 sec times minutes
        settings->setValue("sessionInterval", sessionInterval);
    }
    if (!settings->contains("seriesInterval")){
        qint64 seriesInterval = 60 * 4; // 60 sec times minutes
        settings->setValue("seriesInterval", seriesInterval);
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
    if (cfg.opened) cfg.setBasicStructure();
    return cfg.opened;
}


void DataManager::updateSessions(){
    auto imageDir = this->getImagesPath();
    // get the list of inage files, sorted by creation time
    QFileInfoList fileInfos = imageDir.entryInfoList(settings->value("imagesFilter").toStringList(),QDir::Files, QDir::Time);
    qint64 sessionInterval = getSessionInterval();
    qint64 seriesInterval = getSessionInterval();


    // go to the last save session/series to get the date
    xml_node sessionsNode = cfg.pugi.document_element().child("sessions");
    if (sessionsNode.empty()){}
//    xml_node lastSeries = cfg.pugi.document_element().child("sessions").last_child("session").last_child("series");
//    if (lastSeries.empty()){
//        //create the
//    }
//    for (QFileInfo fileInfo : fileInfos){
//    }

}
qint64 DataManager::getSessionInterval()
{
    return settings->value("sessionInterval").toInt();
}

qint64 DataManager::getSeriesInterval()
{
    return settings->value("seriesInterval").toInt();
}

void config::setBasicStructure()
{
    root = pugi.document_element();
    if (QString(root.name()) != "ArcherAssistant"){
        root.set_name("ArcherAssistant");
        qDebug() << "Setting name";
        setModified();
    }
    xml_node sessions = root.child("sessions");
    if (sessions == nullptr) {
        root.append_child("sessions");
        qDebug() <<"Adding sessions";
        setModified();
    }
}

void config::setModified()
{
    modified = true;
}
