#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QFile>
#include <QDir>

#include <pugixml.hpp>

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr, const QStringList args=QStringList(), const bool gui=true);
    ~DataManager();

    void sayHello();
private: //methods

    QDir getImagesPath();
    void updateSessions();


private: // variables
    const QStringList args;
    const bool gui;

    QSettings *settings;

    pugi::xml_document config;
    QFile *configFile;

signals:


};

#endif // DATAMANAGER_H
