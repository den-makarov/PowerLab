#include "mainwindow/mainwindow.h"
#include "parameters/graphparameterswidget.h"

namespace PowerLab {
namespace Gui {

void MainWindow::showParameters() {
  auto widget = new GraphParametersWidget(this, m_graphWidgetSet);
  createDockWindow(widget, WidgetType::PARAMETERS, "Graph Parameters");
}

} // namespace Gui
} // namespace PowerLab
