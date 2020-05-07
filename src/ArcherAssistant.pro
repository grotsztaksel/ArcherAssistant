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
    data_manager/datamanager.cpp \
    data_manager/worker.cpp \
    gui/sessioncontrolwidget.cpp \
    gui/trainingsessionwindow.cpp \
    gui/mainwindow.cpp \
    model/aatreemodel.cpp \
    main.cpp \
    model/aatreenode_abstract.cpp \
    model/aatreenode_pugi.cpp

HEADERS += \
    data_manager/datamanager.h \
    data_manager/worker.h \
    gui/sessioncontrolwidget.h \
    gui/trainingsessionwindow.h \
    gui/mainwindow.h \
    model/aatreemodel.h \
    model/aatreenode_abstract.h \
    model/aatreenode_pugi.h

FORMS += \
    gui/sessioncontrolwidget.ui \
    gui/trainingsessionwindow.ui \
    gui/mainwindow.ui

INCLUDEPATH += $${PWD}/gui/
INCLUDEPATH += $${PWD}/data_manager/
INCLUDEPATH += $${PWD}/model/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# Tixi library from DLR:
win32: LIBS += -L$$PWD/../lib/TIXI-3.0.0-win64/lib/ -ltixi3

INCLUDEPATH += $$PWD/../lib/TIXI-3.0.0-win64/include/tixi3
DEPENDPATH += $$PWD/../lib/TIXI-3.0.0-win64/include/tixi3

PRE_TARGETDEPS += $$PWD/../lib/TIXI-3.0.0-win64/lib/tixi3.lib

# pugixml
INCLUDEPATH += $$PWD/../lib/pugixml-1.10/src

HEADERS +=  $$PWD/../lib/pugixml-1.10/src/pugixml.hpp \
            $$PWD/../lib/pugixml-1.10/src/pugiconfig.hpp
SOURCES += $$PWD/../lib/pugixml-1.10/src/pugixml.cpp
