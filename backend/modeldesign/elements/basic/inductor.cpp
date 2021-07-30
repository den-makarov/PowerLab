#include "inductor.h"
#include "modeldesign/parameters/inductance.h"

namespace PowerLab {
namespace ModelDesign {

Inductor::Inductor(const ElementName& name)
  : CircuitElement(name)
{
  auto inductance = std::make_unique<Inductance>();
  addParameter(ParameterType::INDUCTANCE, std::move(inductance));

  auto port1 = std::make_unique<ElementPort>(*this);
  auto port2 = std::make_unique<ElementPort>(*this);
  addPort(std::move(port1));
  addPort(std::move(port2));

}

} // namespace ModelDesign
} // namespace PowerLab
