#include "capacitor.h"
#include "modeldesign/parameters/capacitance.h"

namespace PowerLab {
namespace ModelDesign {

Capacitor::Capacitor(const ElementName& name)
  : CircuitElement(name)
{
  auto capacitance = std::make_unique<Capacitance>();
  addParameter(ParameterType::CAPACITANCE, std::move(capacitance));

  auto port1 = std::make_unique<ElementPort>(*this);
  auto port2 = std::make_unique<ElementPort>(*this);
  addPort(std::move(port1));
  addPort(std::move(port2));
}

} // namespace ModelDesign
} // namespace PowerLab
