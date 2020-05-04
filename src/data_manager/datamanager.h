#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QFile>
#include <QDir>

#include <pugixml.hpp>
struct config{
    QFile *file = nullptr;
    pugi::xml_document pugi;
    bool opened = false;
};

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr, const QStringList args=QStringList(), const bool gui=true);
    ~DataManager();

    //! just a dummy function to see if the MainWindow object can communicate with this
    void sayHello();
public slots:
    //! open the config xml file
    bool openConfigFile();
private: //methods
    //! take the input argument xml="<filename>" and save it into the program settings.
    //! If the argument is not present, use the default one
    void setupConfigFile();

    //! read the config xml data and find the information about the location of the images on the drive system
    QDir getImagesPath();

    //! search the paths provided and find all the image files. Check the date of creation, and create a <series> node
    //! in <session> with date and times attributes.
    void updateSessions();


private: // variables
    //! list of input arguments passed from main as QStringList
    const QStringList args;
    //! flag defining if the program was run with (true) or without (false) GUI.
    const bool gui;
    //! program settings
    QSettings *settings = nullptr;
    //! the actual data structure collecting the QFile object and the pugi_xml object to work together
    config cfg;



signals:


};

#endif // DATAMANAGER_H
