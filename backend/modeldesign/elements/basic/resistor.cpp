#include <sstream>
#include <cassert>

#include "resistor.h"
#include "modeldesign/parameters/resistance.h"

namespace PowerLab {
namespace ModelDesign {

Resistor::Resistor(const ElementName& name)
  : CircuitElement(name)
{
  auto resistance = std::make_unique<Resistance>();
  m_parameters.addParameter(ParameterType::RESISTANCE, std::move(resistance));

  auto port1 = std::make_unique<ElementPort>(*this, PortType::POWER_IN);
  auto port2 = std::make_unique<ElementPort>(*this, PortType::POWER_OUT);
  addPort(std::move(port1));
  addPort(std::move(port2));
}

std::string Resistor::getModel() const {
  std::ostringstream model;

  auto& name = getName();
  if(name.empty()) {
    // ERROR
    return "";
  }

  if(name.front() != 'R') {
    // ERROR
    return "";
  }

  model << name;

  auto inPorts = getPortsOfType(PortType::POWER_IN);
  auto outPorts = getPortsOfType(PortType::POWER_OUT);

  if(inPorts.size() != 1 || outPorts.size() != 1) {
    // ERROR
    return "";
  }

  model << " ";
  getConnectionModel(model, &inPorts.front().get());

  model << " ";
  getConnectionModel(model, &outPorts.front().get());

  auto resistance = m_parameters.getParameter(ParameterType::RESISTANCE);
  if(resistance) {
    model << " " << resistance->getValue<double>();
  } else {
    assert(false && "MANDATORY PARAMETER IS LOST: RESISTANCE");
    model << " 0.0";
  }

  return model.str();
}

} // namespace ModelDesign
} // namespace PowerLab
