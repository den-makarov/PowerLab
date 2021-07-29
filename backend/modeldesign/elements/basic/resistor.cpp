#include "resistor.h"
#include "modeldesign/parameters/resistance.h"

namespace PowerLab {
namespace ModelDesign {

Resistor::Resistor(const ElementName& name)
  : CircuitElement(name)
{
  auto resistance = std::make_unique<Resistance>();
  addParameter(parameterTypeToString(ParameterType::RESISTANCE), std::move(resistance));

  auto port1 = std::make_unique<ElementPort>(*this);
  auto port2 = std::make_unique<ElementPort>(*this);
  addPort(std::move(port1));
  addPort(std::move(port2));
}

} // namespace ModelDesign
} // namespace PowerLab
