#include <iostream>

#include <QApplication>

#include "mainwindow/mainwindow.h"
#include "version.h"
#include "logger.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QString appName = QObject::tr(POWERLAB_APP_NAME);
  QString appVersion = POWERLAB_APP_VERSION;
  QString appTitle = appName + " - " + appVersion;

  PowerLab::Logger::LogProvider::instance().addStream(std::cout);
  PowerLab::Logger::log(PowerLab::System::Message::DEBUG_APPLICATION_START,
                        appTitle.toStdString());

  QCoreApplication::setApplicationVersion(appVersion);
  QCoreApplication::setApplicationName(appTitle);

  PowerLab::Gui::MainWindow window;

  auto msgHunter = [&window](std::string msg){
    window.debugMsg(msg);
  };

  PowerLab::Logger::LogStreamHunter streamHunter(msgHunter);
  PowerLab::Logger::LogProvider::instance().addStreamHunter(streamHunter);

  window.show();
  return app.exec();
}
