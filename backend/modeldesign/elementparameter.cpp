#include <limits>
#include <map>

#include "elementparameter.h"
#include "logger.h"

namespace {

const std::map<PowerLab::ModelDesign::ParameterType, std::string> UNITS_MAP = {
  { PowerLab::ModelDesign::ParameterType::RESISTANCE, "Ohm" },
  { PowerLab::ModelDesign::ParameterType::INDUCTANCE, "H" },
  { PowerLab::ModelDesign::ParameterType::CAPACITANCE, "F" },
  { PowerLab::ModelDesign::ParameterType::VOLTAGE, "V" },
  { PowerLab::ModelDesign::ParameterType::CURRENT, "A" },
  { PowerLab::ModelDesign::ParameterType::TEMPERATURE, "C" },
  { PowerLab::ModelDesign::ParameterType::LENGTH, "m" },
  { PowerLab::ModelDesign::ParameterType::WIDTH, "m" },
  { PowerLab::ModelDesign::ParameterType::AREA, "m2" },
  { PowerLab::ModelDesign::ParameterType::VOLUME, "m3" },
  { PowerLab::ModelDesign::ParameterType::QUANTITY, "" },
};

std::string getStringName(PowerLab::ModelDesign::ParameterType type) {
  std::string name = "";
  switch(type) {
  case PowerLab::ModelDesign::ParameterType::RESISTANCE: name = "resistance"; break;
  case PowerLab::ModelDesign::ParameterType::INDUCTANCE: name = "inductance"; break;
  case PowerLab::ModelDesign::ParameterType::CAPACITANCE: name = "capacitance"; break;
  case PowerLab::ModelDesign::ParameterType::VOLTAGE: name = "voltage"; break;
  case PowerLab::ModelDesign::ParameterType::CURRENT: name = "current"; break;
  case PowerLab::ModelDesign::ParameterType::TEMPERATURE: name = "temperature"; break;
  case PowerLab::ModelDesign::ParameterType::LENGTH: name = "length"; break;
  case PowerLab::ModelDesign::ParameterType::WIDTH: name = "width"; break;
  case PowerLab::ModelDesign::ParameterType::AREA: name = "area"; break;
  case PowerLab::ModelDesign::ParameterType::VOLUME: name = "volume"; break;
  case PowerLab::ModelDesign::ParameterType::QUANTITY: name = "quantity"; break;
  }
  return name;
}

}

namespace PowerLab {
namespace ModelDesign {

std::string parameterTypeToString(ParameterType type) {
  return getStringName(type);
}

ElementParameter::ElementParameter(const std::string& name)
  : m_name(name)
{
}

const std::string& ElementParameter::getName() const {
  return m_name;
}

ParameterType ElementParameter::getType() const {
  return ParameterType::QUANTITY;
}

const std::string& ElementParameter::getUnits() const {
  return UNITS_MAP.at(ElementParameter::getType());
}

void ElementParameter::getValueImpl(const double** pointer) const {
  static double INVALID_VALUE = std::numeric_limits<double>::quiet_NaN();
  *pointer = &INVALID_VALUE;
}

void ElementParameter::setValueImpl(double) {

}

void ElementParameter::getValueImpl(const int** pointer) const {
  static int INVALID_VALUE = std::numeric_limits<int>::min();
  *pointer = &INVALID_VALUE;
}

void ElementParameter::setValueImpl(int) {

}

void ElementParameter::getValueImpl(const std::string** pointer) const {
  static std::string INVALID_VALUE = "INVALID_VALUE";
  *pointer = &INVALID_VALUE;
}

void ElementParameter::setValueImpl(const std::string&) {
}

Resistance::Resistance(double value)
  : DoubleElementParameter(getStringName(ParameterType::RESISTANCE))
  , m_value(value)
{
}

ParameterType Resistance::getType() const {
  return ParameterType::RESISTANCE;
}

const std::string& Resistance::getUnits() const {
  return UNITS_MAP.at(getType());
}

void Resistance::getValueImpl(const double** pointer) const {
  *pointer = &m_value;
}

void Resistance::setValueImpl(double value) {
  m_value = value;
}

} // namespace ModelDesign
} // namespace PowerLab
