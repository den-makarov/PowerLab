#include "frequency.h"

namespace PowerLab {
namespace ModelDesign {

Frequency::Frequency(double value)
  : FloatElementParameter(value)
{
}

ParameterType Frequency::getType() const {
  return ParameterType::FREQUENCY;
}

} // namespace ModelDesign
} // namespace PowerLab
