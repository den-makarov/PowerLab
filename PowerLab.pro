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
    backend/modelresult/modelresultmeta.cpp \
    backend/modelresult/modelresult.cpp \
    backend/modelresult/modelresultvalues.cpp \
    backend/modelresult/modelresultvalidator.cpp \
    backend/logger/logger.cpp \
    backend/logger/message.cpp \
    backend/logger/system_message.cpp \
    backend/logger/gui_message.cpp \
    backend/logger/model_message.cpp \
    backend/utils/string_utils.cpp \
    gui/library/librarywidget.cpp \
    gui/main.cpp \
    gui/dialogs/metadatawindow.cpp \
    gui/mainwindow/mainwindow.cpp \
    gui/mainwindow/mainwindow_actions.cpp \
    gui/mainwindow/mainwindow_controls.cpp \
    gui/mainwindow/mainwindow_model_results.cpp \
    gui/mainwindow/mainwindow_model_designs.cpp \
    gui/mainwindow/mainwindow_parameters.cpp \
    gui/mainwindow/mainwindow_component_library.cpp \
    gui/graphs/graphprocessor.cpp \
    gui/graphs/graphwidget.cpp \
    gui/graphs/plot.cpp \
    gui/model/modelwidget.cpp \
    gui/parameters/parameterswidget.cpp

HEADERS += \
    backend/modelresult/modelresultmeta.h \
    backend/modelresult/modelresultvalidator.h \
    backend/modelresult/modelresult.h \
    backend/modelresult/modelresultvalues.h \
    backend/logger/logger.h \
    backend/logger/message.h \
    backend/logger/system_message.h \
    backend/logger/model_message.h \
    backend/logger/gui_message.h \
    backend/version.h \
    backend/utils/string_utils.h \
    gui/library/librarywidget.h \
    gui/mainwindow/mainwindow.h \
    gui/dialogs/metadatawindow.h \
    gui/graphs/graphprocessor.h \
    gui/graphs/graphwidget.h \
    gui/graphs/plot.h \
    gui/model/modelwidget.h \
    gui/parameters/parameterswidget.h

TRANSLATIONS += \
    PowerLab_en_US.ts

INCLUDEPATH += \
    include \
    backend \
    gui \
    backend/utils \
    backend/logger

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
