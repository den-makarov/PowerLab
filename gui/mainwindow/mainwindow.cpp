#include <QGuiApplication>

#include "mainwindow/mainwindow.h"

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
}

} // namespace Gui
