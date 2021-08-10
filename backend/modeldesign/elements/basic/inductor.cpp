#include <sstream>
#include <cassert>

#include "inductor.h"
#include "modeldesign/parameters/inductance.h"

namespace PowerLab {
namespace ModelDesign {

Inductor::Inductor(const ElementName& name)
  : CircuitElement(name)
{
  auto inductance = std::make_unique<Inductance>();
  m_parameters.addParameter(ParameterType::INDUCTANCE, std::move(inductance));

  auto port1 = ElementPort::createPort(*this, PortType::POWER_IN);
  auto port2 = ElementPort::createPort(*this, PortType::POWER_OUT);
  addPort(port1);
  addPort(port2);
}

std::string Inductor::getModel() const {
  std::ostringstream model;

  auto& name = getName();
  if(name.empty()) {
    // ERROR
    return "";
  }

  if(name.front() != 'L') {
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
  getConnectionModel(model, inPorts.front());

  model << " ";
  getConnectionModel(model, outPorts.front());

  auto resistance = m_parameters.getParameter(ParameterType::INDUCTANCE);
  if(resistance) {
    model << " " << resistance->getValue<double>();
  } else {
    assert(false && "MANDATORY PARAMETER IS LOST: INDUCTANCE");
    model << " 0.0";
  }

  return model.str();
}

} // namespace ModelDesign
} // namespace PowerLab
