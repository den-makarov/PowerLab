#include "mainwindow/mainwindow.h"
#include "model/modelwidget.h"

namespace Gui {

void MainWindow::addDefaultModelDesignWidget() {
  auto widget = new ModelWidget(this);
  widget->setWindowModified(true);
  setCentralWidget(widget);
  //  createDockWindow(widget, WidgetType::MODEL_DESIGN, "Untitled");
}

} // namespace Gui
