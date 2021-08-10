#include <sstream>

#include "switch.h"
#include "modeldesign/parameters/switchstate.h"

namespace PowerLab {
namespace ModelDesign {

Switch::Switch(const ElementName& name)
  : CircuitElement(name)
{
  auto initialStatus = std::make_unique<SwitchStatus>(SwitchState(SwitchState::State::OFF));
  m_parameters.addParameter(ParameterType::STATE, std::move(initialStatus));

  auto powerPort1 = ElementPort::createPort(*this, PortType::POWER_IN);
  auto powerPort2 = ElementPort::createPort(*this, PortType::POWER_OUT);
  auto controlPort1 = ElementPort::createPort(*this, PortType::CONTROL_IN);
  auto controlPort2 = ElementPort::createPort(*this, PortType::CONTROL_OUT);

  addPort(powerPort1);
  addPort(powerPort2);
  addPort(controlPort1);
  addPort(controlPort2);
}

std::string Switch::getModel() const {
  std::ostringstream model;

  auto& name = getName();
  if(name.empty()) {
    // ERROR
    return "";
  }

  if(name.front() != 'S') {
    // ERROR
    return "";
  }

  model << name;

  auto inPorts = getPortsOfType(PortType::POWER_IN);
  auto outPorts = getPortsOfType(PortType::POWER_OUT);
  auto inControlPorts = getPortsOfType(PortType::CONTROL_IN);
  auto outControlPorts = getPortsOfType(PortType::CONTROL_OUT);

  if(inPorts.size() != 1 || outPorts.size() != 1 || inControlPorts.size() != 1 || outControlPorts.size() != 1 ) {
    // ERROR
    return "";
  }

  model << " ";
  getConnectionModel(model, inPorts.front());

  model << " ";
  getConnectionModel(model, outPorts.front());

  model << " ";
  getConnectionModel(model, inControlPorts.front());

  model << " ";
  getConnectionModel(model, outControlPorts.front());

  auto initialStatus = m_parameters.getParameter(ParameterType::STATE);
  if(initialStatus) {
    model << " " << SwitchState(initialStatus->getValue<int>()).str();
  } else {
    // WARNING: default switch state
    model << " " << SwitchState(SwitchState::State::OFF).str();
  }

  return model.str();
}

} // namespace ModelDesign
} // namespace PowerLab
