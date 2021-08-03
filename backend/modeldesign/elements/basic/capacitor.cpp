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

} // namespace ModelDesign
} // namespace PowerLab
