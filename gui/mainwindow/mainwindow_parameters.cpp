#include "mainwindow/mainwindow.h"
#include "parameters/parameterswidget.h"

namespace Gui {

void MainWindow::showParameters() {
  auto widget = new ParametersWidget(this);
  createDockWindow(widget, WidgetType::PARAMETERS, "Parameters");
}

} // namespace Gui
