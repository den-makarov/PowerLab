#include <QDockWidget>

#include "mainwindow/mainwindow.h"
#include "parameters/graphparameterswidget.h"

namespace PowerLab {
namespace Gui {

void MainWindow::showParameters() {
  if(!m_graphParameters) {
    m_graphParameters = new GraphParametersWidget(this, m_graphWidgetSet);
    createDockWindow(m_graphParameters, WidgetType::PARAMETERS, tr("Graph Parameters"));
    connect(this, &MainWindow::newGraphWidget, [this](QWidget*){
      this->m_graphParameters->updateGraphList(m_graphWidgetSet);
    });
  } else {
    // @TODO: show graphParamsDock
    m_graphParameters->updateGraphList(m_graphWidgetSet);
    for(auto dock : m_docksList) {
      if(dock->windowTitle() == tr("Graph Parameters")) {
        dock->show();
      }
    }
  }
}

} // namespace Gui
} // namespace PowerLab
