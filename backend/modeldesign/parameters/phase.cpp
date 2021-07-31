#include "phase.h"

namespace PowerLab {
namespace ModelDesign {

Phase::Phase(double value)
  : FloatElementParameter(value)
{
}

ParameterType Phase::getType() const {
  return ParameterType::PHASE;
}

} // namespace ModelDesign
} // namespace PowerLab
