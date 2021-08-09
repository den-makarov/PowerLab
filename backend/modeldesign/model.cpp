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

  ModelDesign::Connection ground = ModelDesign::ElementConnection::createConnection();
  m_elements["VA1"]->getAllPorts()[1].get().connect(ground);
  m_elements["R1"]->getAllPorts()[1].get().connect(ground);
  m_elements["C1"]->getAllPorts()[1].get().connect(ground);

  ModelDesign::Connection input = ModelDesign::ElementConnection::createConnection();
  m_elements["VA1"]->getAllPorts()[0].get().connect(input);
  m_elements["L1"]->getAllPorts()[0].get().connect(input);

  ModelDesign::Connection output = ModelDesign::ElementConnection::createConnection();
  m_elements["L1"]->getAllPorts()[1].get().connect(output);
  m_elements["R1"]->getAllPorts()[0].get().connect(output);
  m_elements["C1"]->getAllPorts()[0].get().connect(output);

  Logger::log(Logger::Message::DEBUG_MSG, ground->str());
  Logger::log(Logger::Message::DEBUG_MSG, input->str());
  Logger::log(Logger::Message::DEBUG_MSG, output->str());

  m_elements["L1"]->getAllPorts()[1].get().disconnect();
  input->disconnectPort(m_elements["L1"]->getAllPorts()[0].get());
  for(auto& [name, item] : m_elements) {
    auto model = item->getModel();
    Logger::log(Logger::Message::DEBUG_MSG, model);
  }
}

} // namespace ModelDesign
} // namespace PowerLab
