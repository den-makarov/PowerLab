#include "quantity.h"

namespace PowerLab {
namespace ModelDesign {

Quantity::Quantity(double value)
  : FloatElementParameter(value)
{
}

ParameterType Quantity::getType() const {
  return ParameterType::QUANTITY;
}

} // namespace ModelDesign
} // namespace PowerLab
