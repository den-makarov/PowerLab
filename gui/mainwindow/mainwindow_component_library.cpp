#include "mainwindow/mainwindow.h"
#include "library/librarywidget.h"

namespace Gui {

void MainWindow::showLibrary() {
  auto widget = new LibraryWidget(this);
  createDockWindow(widget, WidgetType::LIBRARY, "Library");
}

} // namespace Gui
