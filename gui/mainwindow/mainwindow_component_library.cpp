#include "mainwindow/mainwindow.h"
#include "library/librarywidget.h"

namespace PowerLab {
namespace Gui {

void MainWindow::showLibrary() {
  auto widget = new LibraryWidget(this);
  createDockWindow(widget, WidgetType::LIBRARY, "Library");
}

} // namespace Gui
} // namespace PowerLab
