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
public slots:
    bool openConfigFile();
private: //methods

    QDir getImagesPath();
    void updateSessions();


private: // variables
    const QStringList args;
    const bool gui;
    pugi::xml_document config;

    QSettings *settings = nullptr;
    QFile *configFile = nullptr;


    void setupConfigFile();

signals:


};

#endif // DATAMANAGER_H
