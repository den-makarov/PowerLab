#include "current.h"

namespace PowerLab {
namespace ModelDesign {

Current::Current(double value)
  : FloatElementParameter(value)
{
}

ParameterType Current::getType() const {
  return ParameterType::CURRENT;
}

} // namespace ModelDesign
} // namespace PowerLab
