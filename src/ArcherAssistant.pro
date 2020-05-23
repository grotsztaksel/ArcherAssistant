QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

UI_DIR = ui

SOURCES += \
    application/aacore.cpp \
    application/aafilemanager.cpp \
    application/aaobject.cpp \
    application/aasessionmanager.cpp \
    application/aasettingsmanager.cpp \
    application/datamanager.cpp \
    application/exifreader.cpp \
    gui/demowindow.cpp \
    gui/filemanagerwidget.cpp \
    gui/filemanagerwindow.cpp \
    gui/maingraphicscene.cpp \
    gui/mainmodeltreeview.cpp \
    gui/mainwindow.cpp \
    gui/pathviewproxymodel.cpp \
    gui/sessioncontrolwidget.cpp \
    gui/trainingsessionwindow.cpp \
    model/aatreemodel.cpp \
    main.cpp \
    model/aatreenode_abstract.cpp \
    model/aatreenode_pugi.cpp

HEADERS += \
    application/aacore.h \
    application/aafilemanager.h \
    application/aaobject.h \
    application/aasessionmanager.h \
    application/aasettingsmanager.h \
    application/datamanager.h \
    application/exifreader.h \
    gui/demowindow.h \
    gui/filemanagerwidget.h \
    gui/filemanagerwindow.h \
    gui/maingraphicscene.h \
    gui/mainmodeltreeview.h \
    gui/mainwindow.h \
    gui/pathviewproxymodel.h \
    gui/sessioncontrolwidget.h \
    gui/trainingsessionwindow.h \
    include/settings.h \
    model/aatreemodel.h \
    model/aatreenode_abstract.h \
    model/aatreenode_pugi.h

FORMS += \
    gui/demowindow.ui \
    gui/filemanagerwidget.ui \
    gui/filemanagerwindow.ui \
    gui/mainwindow.ui \
    gui/sessioncontrolwidget.ui \
    gui/trainingsessionwindow.ui

INCLUDEPATH += $${PWD}/gui/
INCLUDEPATH += $${PWD}/application/
INCLUDEPATH += $${PWD}/model/
INCLUDEPATH += $${PWD}/include/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# pugixml
INCLUDEPATH += $$PWD/../lib/pugixml-1.10/src

HEADERS +=  $$PWD/../lib/pugixml-1.10/src/pugixml.hpp \
            $$PWD/../lib/pugixml-1.10/src/pugiconfig.hpp
SOURCES += $$PWD/../lib/pugixml-1.10/src/pugixml.cpp


# easy exif
INCLUDEPATH += $$PWD/../lib/easyexif
HEADERS +=  $$PWD/../lib/easyexif/exif.h
SOURCES += $$PWD/../lib/easyexif/exif.cpp
