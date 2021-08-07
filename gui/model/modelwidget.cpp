#include <QGraphicsScene>
#include <QGraphicsItem>

#include "modelwidget.h"
#include "modeldesign/elements/basic/resistor.h"
#include "modeldesign/elements/basic/capacitor.h"
#include "modeldesign/elements/basic/inductor.h"
#include "modeldesign/elements/basic/switch.h"
#include "modeldesign/elements/sources/voltagesource.h"
#include "modeldesign/parameters/switchstate.h"
#include "modeldesign/elementconnectionmanager.h"
#include "modeldesign/elementconnection.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

ModelWidget::ModelWidget(QWidget *parent, const QString& title)
  : QWidget(parent)
  , m_scene(new QGraphicsScene(this))
{
  setToolTip(tr("Model Design"));
  setWindowTitle(title);

  std::vector<std::unique_ptr<ModelDesign::CircuitElement>> elements;

  auto R1 = elements.size();
  elements.emplace_back(new ModelDesign::Resistor("R1"));
  auto L1 = elements.size();
  elements.emplace_back(new ModelDesign::Inductor("L1"));
  auto C1 = elements.size();
  elements.emplace_back(new ModelDesign::Capacitor("C1"));
  auto VA1 = elements.size();
  elements.emplace_back(new ModelDesign::AcVoltageSource("VA1"));

  auto& manager = ModelDesign::ElementConnectionManager::instance();

  ModelDesign::Connection ground(manager.createConnection());
  ground.connectPort(elements[VA1]->getAllPorts()[1]);
  ground.connectPort(elements[R1]->getAllPorts()[1]);
  ground.connectPort(elements[C1]->getAllPorts()[1]);

  ModelDesign::Connection input(manager.createConnection());
  input.connectPort(elements[VA1]->getAllPorts()[0]);
  input.connectPort(elements[L1]->getAllPorts()[0]);

  ModelDesign::Connection output(manager.createConnection());
  output.connectPort(elements[L1]->getAllPorts()[1]);
  output.connectPort(elements[R1]->getAllPorts()[0]);
  output.connectPort(elements[C1]->getAllPorts()[0]);

  for(auto& item : elements) {
    auto model = item->getModel();
    Logger::log(Logger::Message::DEBUG_MSG, model);
  }
}

} // namespace Gui
} // namespace PowerLab
