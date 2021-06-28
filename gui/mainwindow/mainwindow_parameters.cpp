#include "mainwindow/mainwindow.h"
#include "parameters/parameterswidget.h"

namespace PowerLab {
namespace Gui {

void MainWindow::showParameters() {
  auto widget = new ParametersWidget(this);
  createDockWindow(widget, WidgetType::PARAMETERS, "Parameters");
}

} // namespace Gui
} // namespace PowerLab
