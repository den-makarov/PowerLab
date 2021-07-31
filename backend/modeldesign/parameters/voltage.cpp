#include "voltage.h"

namespace PowerLab {
namespace ModelDesign {

Voltage::Voltage(double value)
  : FloatElementParameter(value)
{
}

ParameterType Voltage::getType() const {
  return ParameterType::VOLTAGE;
}

} // namespace ModelDesign
} // namespace PowerLab
