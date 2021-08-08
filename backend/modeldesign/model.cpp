#include "model.h"
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
namespace ModelDesign {

Model::Model(const std::string& name)
  : m_name(name)
{
  m_elements.emplace("R1", new ModelDesign::Resistor("R1"));
  m_elements.emplace("L1", new ModelDesign::Inductor("L1"));
  m_elements.emplace("C1", new ModelDesign::Capacitor("C1"));
  m_elements.emplace("VA1", new ModelDesign::AcVoltageSource("VA1"));

  auto& manager = *m_connectionManager.get();

  ModelDesign::Connection ground(manager.createConnection());
  ground.connectPort(m_elements["VA1"]->getAllPorts()[1]);
  ground.connectPort(m_elements["R1"]->getAllPorts()[1]);
  ground.connectPort(m_elements["C1"]->getAllPorts()[1]);

  ModelDesign::Connection input(manager.createConnection());
  input.connectPort(m_elements["VA1"]->getAllPorts()[0]);
  input.connectPort(m_elements["L1"]->getAllPorts()[0]);

  ModelDesign::Connection output(manager.createConnection());
  output.connectPort(m_elements["L1"]->getAllPorts()[1]);
  output.connectPort(m_elements["R1"]->getAllPorts()[0]);
  output.connectPort(m_elements["C1"]->getAllPorts()[0]);

  for(auto& [name, item] : m_elements) {
    auto model = item->getModel();
    Logger::log(Logger::Message::DEBUG_MSG, model);
  }
}

} // namespace ModelDesign
} // namespace PowerLab
