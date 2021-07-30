#include "resistance.h"

namespace PowerLab {
namespace ModelDesign {

Resistance::Resistance(double value)
  : FloatElementParameter(value)
{
}

ParameterType Resistance::getType() const {
  return ParameterType::RESISTANCE;
}

} // namespace ModelDesign
} // namespace PowerLab
