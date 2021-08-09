#include <sstream>
#include <cassert>

#include "capacitor.h"
#include "modeldesign/parameters/capacitance.h"

namespace PowerLab {
namespace ModelDesign {

Capacitor::Capacitor(const ElementName& name)
  : CircuitElement(name)
{
  auto capacitance = std::make_unique<Capacitance>();
  m_parameters.addParameter(ParameterType::CAPACITANCE, std::move(capacitance));

  auto port1 = std::make_unique<ElementPort>(*this, PortType::POWER_IN);
  auto port2 = std::make_unique<ElementPort>(*this, PortType::POWER_OUT);
  addPort(std::move(port1));
  addPort(std::move(port2));
}

std::string Capacitor::getModel() const {
  std::ostringstream model;

  auto& name = getName();
  if(name.empty()) {
    // ERROR
    return "";
  }

  if(name.front() != 'C') {
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

  auto resistance = m_parameters.getParameter(ParameterType::CAPACITANCE);
  if(resistance) {
    model << " " << resistance->getValue<double>();
  } else {
    assert(false && "MANDATORY PARAMETER IS LOST: CAPACITANCE");
    model << " 0.0";
  }

  return model.str();
}

} // namespace ModelDesign
} // namespace PowerLab
