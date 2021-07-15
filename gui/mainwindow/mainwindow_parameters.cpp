#include <QDockWidget>

#include "mainwindow/mainwindow.h"
#include "parameters/graphparameterswidget.h"

namespace PowerLab {
namespace Gui {

bool MainWindow::createParametersWidgets() {
  bool result = true;

  m_graphParameters = new GraphParametersWidget(this, m_graphWidgetSet);

  connect(this, &MainWindow::newGraphWidget, [this](QWidget*){
    this->m_graphParameters->updateGraphList(m_graphWidgetSet);
  });

  if(!createDockWindow(m_graphParameters, WidgetType::PARAMETERS, tr("Graph Parameters"))) {
    result = false;
  }

  // @TODO: Add creation of Model design parameters widget

  return result;
}

void MainWindow::showParameters() {
  // @TODO: Check what widget type is in focus
  m_graphParameters->updateGraphList(m_graphWidgetSet);
  for(auto dock : m_docksList) {
    if(dock->windowTitle() == tr("Graph Parameters")) {
      if(dock->isHidden()) {
        dock->setHidden(false);
      } else {
        dock->setHidden(true);
      }
    }
  }
}

} // namespace Gui
} // namespace PowerLab
