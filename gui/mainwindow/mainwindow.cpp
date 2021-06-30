#include <QGuiApplication>

#include "mainwindow/mainwindow.h"

namespace PowerLab {
namespace Gui {

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{ 
  setWindowState(Qt::WindowState::WindowMaximized);

  createActions();
  createStatusBar();
  addDefaultModelDesignWidget();
  setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowTabbedDocks | QMainWindow::AllowNestedDocks);
  setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

  readSettings();

  QGuiApplication::setFallbackSessionManagementEnabled(false);
  connect(qApp, &QGuiApplication::commitDataRequest,
          this, &MainWindow::commitData);

  setCurrentFile(QString());
  setUnifiedTitleAndToolBarOnMac(true);

  const QIcon appIcon = QIcon::fromTheme("usage-app", QIcon(":/images/app.png"));
  setWindowIcon(appIcon);
}

} // namespace Gui
} // namespace PowerLab
