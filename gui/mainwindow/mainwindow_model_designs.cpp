#include "mainwindow/mainwindow.h"

namespace Gui {

void MainWindow::addDefaultModelDesignWidget() {
  QWidget* widget = new QWidget(this);
  createDockWindow(widget, WidgetType::MODEL_DESIGN);
}

} // namespace Gui
