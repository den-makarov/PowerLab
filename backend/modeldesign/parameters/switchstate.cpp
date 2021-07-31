#include "switchstate.h"

namespace PowerLab {
namespace ModelDesign {

SwitchStatus::SwitchStatus(SwitchState state)
  : StateElementParameter(state.state<int>())
{
}

ParameterType SwitchStatus::getType() const {
  return ParameterType::STATE;
}

} // namespace ModelDesign
} // namespace PowerLab
