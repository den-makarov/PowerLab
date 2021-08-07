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

  auto powerPort1 = std::make_unique<ElementPort>(*this, PortType::POWER_IN);
  auto powerPort2 = std::make_unique<ElementPort>(*this, PortType::POWER_OUT);
  auto controlPort1 = std::make_unique<ElementPort>(*this, PortType::CONTROL_IN);
  auto controlPort2 = std::make_unique<ElementPort>(*this, PortType::CONTROL_OUT);

  addPort(std::move(powerPort1));
  addPort(std::move(powerPort2));
  addPort(std::move(controlPort1));
  addPort(std::move(controlPort2));
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

  model << " " << Connection(inPorts.front().get().getConnection()).getModel();
  model << " " << Connection(outPorts.front().get().getConnection()).getModel();
  model << " " << Connection(inControlPorts.front().get().getConnection()).getModel();
  model << " " << Connection(outControlPorts.front().get().getConnection()).getModel();

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
