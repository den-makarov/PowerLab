QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backend/logger/guimessage.cpp \
    backend/logger/modelresultmessage.cpp \
    backend/logger/modeldesignmessage.cpp \
    backend/logger/systemmessage.cpp \
    backend/modeldesign/elementparameter.cpp \
    backend/modeldesign/abstractelement.cpp \
    backend/modeldesign/elementconnection.cpp \
    backend/modeldesign/elementconnectionmanager.cpp \
    backend/modeldesign/elementport.cpp \
    backend/modeldesign/elements/basic/capacitor.cpp \
    backend/modeldesign/elements/basic/inductor.cpp \
    backend/modeldesign/elements/basic/resistor.cpp \
    backend/modeldesign/elements/basic/switch.cpp \
    backend/modeldesign/elements/sources/source.cpp \
    backend/modeldesign/elements/sources/voltagesource.cpp \
    backend/modeldesign/elements/sources/waveformsource.cpp \
    backend/modeldesign/parameters/capacitance.cpp \
    backend/modeldesign/parameters/inductance.cpp \
    backend/modeldesign/parameters/resistance.cpp \
    backend/modelresult/modelresultmeta.cpp \
    backend/modelresult/modelresult.cpp \
    backend/modelresult/modelresultvalues.cpp \
    backend/modelresult/modelresultvalidator.cpp \
    backend/logger/logger.cpp \
    backend/logger/message.cpp \
    backend/utils/mathutils.cpp \
    backend/utils/stringutils.cpp \
    gui/elements/drawingitem.cpp \
    gui/library/librarywidget.cpp \
    gui/main.cpp \
    gui/dialogs/metadatawindow.cpp \
    gui/mainwindow/mainwindow.cpp \
    gui/graphs/graphprocessor.cpp \
    gui/graphs/graphwidget.cpp \
    gui/graphs/graphparametersmodel.cpp \
    gui/graphs/plot.cpp \
    gui/graphs/zoomselectionrectarea.cpp \
    gui/mainwindow/mainwindowactions.cpp \
    gui/mainwindow/mainwindowcomponentlibrary.cpp \
    gui/mainwindow/mainwindowcontrols.cpp \
    gui/mainwindow/mainwindowmodeldesigns.cpp \
    gui/mainwindow/mainwindowmodelresults.cpp \
    gui/mainwindow/mainwindowparameters.cpp \
    gui/model/modelwidget.cpp \
    gui/parameters/graphparameterswidget.cpp \
    gui/parameters/parameterswidget.cpp

HEADERS += \
    backend/logger/guimessage.h \
    backend/logger/modelresultmessage.h \
    backend/logger/modeldesignmessage.h \
    backend/logger/systemmessage.h \
    backend/modeldesign/elementparameter.h \
    backend/modeldesign/abstractelement.h \
    backend/modeldesign/elementport.h \
    backend/modeldesign/elementconnectionmanager.h \
    backend/modeldesign/elementconnection.h \
    backend/modeldesign/elements/basic/capacitor.h \
    backend/modeldesign/elements/basic/inductor.h \
    backend/modeldesign/elements/basic/resistor.h \
    backend/modeldesign/elements/basic/switch.h \
    backend/modeldesign/elements/sources/source.h \
    backend/modeldesign/elements/sources/voltagesource.h \
    backend/modeldesign/elements/sources/waveformsource.h \
    backend/modeldesign/parameters/capacitance.h \
    backend/modeldesign/parameters/inductance.h \
    backend/modeldesign/parameters/resistance.h \
    backend/modelresult/modelresultmeta.h \
    backend/modelresult/modelresultvalidator.h \
    backend/modelresult/modelresult.h \
    backend/modelresult/modelresultvalues.h \
    backend/logger/logger.h \
    backend/logger/message.h \
    backend/utils/mathutils.h \
    backend/utils/stringutils.h \
    backend/version.h \
    gui/elements/drawingitem.h \
    gui/library/librarywidget.h \
    gui/mainwindow/mainwindow.h \
    gui/dialogs/metadatawindow.h \
    gui/graphs/graphprocessor.h \
    gui/graphs/graphwidget.h \
    gui/graphs/graphparametersmodel.h \
    gui/graphs/plot.h \
    gui/graphs/zoomselectionrectarea.h \
    gui/model/modelwidget.h \
    gui/parameters/graphparameterswidget.h \
    gui/parameters/parameterswidget.h

TRANSLATIONS += \
    PowerLab_en_US.ts

INCLUDEPATH += \
    include \
    backend \
    gui \
    backend/utils \
    backend/logger

RESOURCES = powerlab.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
