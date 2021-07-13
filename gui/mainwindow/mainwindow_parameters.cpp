#include "mainwindow/mainwindow.h"
#include "parameters/graphparameterswidget.h"

namespace PowerLab {
namespace Gui {

void MainWindow::showParameters() {
  if(!m_graphParameters) {
    m_graphParameters = new GraphParametersWidget(this, m_graphWidgetSet);
    createDockWindow(m_graphParameters, WidgetType::PARAMETERS, "Graph Parameters");
  } else {
    // @TODO: show graphParamsDock
    m_graphParameters->updateGraphList(m_graphWidgetSet);
  }
}

} // namespace Gui
} // namespace PowerLab
