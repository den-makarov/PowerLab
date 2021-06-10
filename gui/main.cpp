#include <iostream>
#include <QApplication>

#include "mainwindow.h"
#include "version.h"
#include "logger.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QString appName = QObject::tr(ELECTRONSHIK_PROGRAM_NAME);
  QString appVersion = ELECTRONSHIK_VERSION;
  QString appTitle = appName + " - " + appVersion;

  Logger::LogProvider::instance().addStream(std::cout);
  Logger::log(System::SystemMessage::DEBUG_APPLICATION_START, appTitle.toStdString());

  QCoreApplication::setApplicationVersion(appVersion);
  QCoreApplication::setApplicationName(appTitle);

  Gui::MainWindow w;
  w.show();
  return app.exec();
}
