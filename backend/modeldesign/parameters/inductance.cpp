#include "inductance.h"

namespace PowerLab {
namespace ModelDesign {

Inductance::Inductance(double value)
  : FloatElementParameter(value)
{
}

ParameterType Inductance::getType() const {
  return ParameterType::INDUCTANCE;
}

} // namespace ModelDesign
} // namespace PowerLab
