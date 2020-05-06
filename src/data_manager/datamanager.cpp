#include "datamanager.h"

#include <QDebug>

using namespace pugi;
DataManager::DataManager(QObject* parent) : QObject(parent) {}

void DataManager::setBasicStructure() {
  root = pugi.document_element();
  if (QString(root.name()) != "ArcherAssistant") {
    root.set_name("ArcherAssistant");
    qDebug() << "Setting name";
    setModified();
  }
  xml_node sessions = root.child("sessions");
  if (sessions == nullptr) {
    root.append_child("sessions");
    qDebug() << "Adding sessions";
    setModified();
  }
}

DataManager::~DataManager() {
  if (opened && modified) {
    pugi.save_file(file->fileName().toStdString().c_str(), "  ");
    qDebug() << "Modified file" << file->fileName();
  }
}

void DataManager::setModified() {
  modified = true;
}
