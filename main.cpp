#include <QApplication>

#include "mainwindow.h"
#include "version.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QString appName = QObject::tr(ELECTRONSHIK_PROGRAM_NAME);
  QString appVersion = ELECTRONSHIK_VERSION_MAJOR"."
                       ELECTRONSHIK_VERSION_MINOR"."
                       ELECTRONSHIK_VERSION_BUILD;
  QString appTitle = appName + " - " + appVersion;

  QCoreApplication::setApplicationVersion(appVersion);
  QCoreApplication::setApplicationName(appTitle);

  MainWindow w;
  w.show();
  return app.exec();
}
