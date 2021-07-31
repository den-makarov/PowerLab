#include "switch.h"
#include "modeldesign/parameters/switchstate.h"

namespace PowerLab {
namespace ModelDesign {

Switch::Switch(const ElementName& name)
  : CircuitElement(name)
{
  auto initialStatus = std::make_unique<SwitchStatus>(SwitchState(SwitchState::State::OFF));
  m_parameters.addParameter(ParameterType::STATE, std::move(initialStatus));

  auto powerPort1 = std::make_unique<ElementPort>(*this);
  auto powerPort2 = std::make_unique<ElementPort>(*this);
  auto controlPort1 = std::make_unique<ElementPort>(*this);
  auto controlPort2 = std::make_unique<ElementPort>(*this);

  addPort(std::move(powerPort1));
  addPort(std::move(powerPort2));
  addPort(std::move(controlPort1));
  addPort(std::move(controlPort2));
}

} // namespace ModelDesign
} // namespace PowerLab
