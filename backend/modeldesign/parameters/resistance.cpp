#include "resistance.h"

namespace PowerLab {
namespace ModelDesign {

Resistance::Resistance(double value)
  : DoubleElementParameter(parameterTypeToString(ParameterType::RESISTANCE))
  , m_value(value)
{
}

ParameterType Resistance::getType() const {
  return ParameterType::RESISTANCE;
}

const std::string& Resistance::getUnits() const {
  return parameterTypeUnits(getType());
}

void Resistance::getValueImpl(const double** pointer) const {
  *pointer = &m_value;
}

void Resistance::setValueImpl(double value) {
  m_value = value;
}

} // namespace ModelDesign
} // namespace PowerLab
