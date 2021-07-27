#include "resistor.h"

namespace PowerLab {
namespace ModelDesign {

Resistor::Resistor(const ElementName& name)
  : AbstractElement(name)
{
  auto resistance = std::make_unique<Resistance>();
  addParameter(resistance->getName(), std::move(resistance));
}

} // namespace ModelDesign
} // namespace PowerLab
