#include "capacitance.h"

namespace PowerLab {
namespace ModelDesign {

Capacitance::Capacitance(double value)
  : FloatElementParameter(value)
{
}

ParameterType Capacitance::getType() const {
  return ParameterType::CAPACITANCE;
}

} // namespace ModelDesign
} // namespace PowerLab
