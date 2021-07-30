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
  { PowerLab::ModelDesign::ParameterType::FREQUENCY, "Hz" },
  { PowerLab::ModelDesign::ParameterType::PERIOD, "s" },
  { PowerLab::ModelDesign::ParameterType::PHASE, "rad" },
  { PowerLab::ModelDesign::ParameterType::TIME, "s" },
  { PowerLab::ModelDesign::ParameterType::TEMPERATURE, "C" },
  { PowerLab::ModelDesign::ParameterType::LENGTH, "m" },
  { PowerLab::ModelDesign::ParameterType::WIDTH, "m" },
  { PowerLab::ModelDesign::ParameterType::AREA, "m2" },
  { PowerLab::ModelDesign::ParameterType::VOLUME, "m3" },
  { PowerLab::ModelDesign::ParameterType::QUANTITY, "" },
};

const std::string& getStringName(PowerLab::ModelDesign::ParameterType type) {
  static std::string name = "";
  switch(type) {
  case PowerLab::ModelDesign::ParameterType::RESISTANCE: name = "resistance"; break;
  case PowerLab::ModelDesign::ParameterType::INDUCTANCE: name = "inductance"; break;
  case PowerLab::ModelDesign::ParameterType::CAPACITANCE: name = "capacitance"; break;
  case PowerLab::ModelDesign::ParameterType::VOLTAGE: name = "voltage"; break;
  case PowerLab::ModelDesign::ParameterType::CURRENT: name = "current"; break;
  case PowerLab::ModelDesign::ParameterType::FREQUENCY: name = "frequency"; break;
  case PowerLab::ModelDesign::ParameterType::PERIOD: name = "period"; break;
  case PowerLab::ModelDesign::ParameterType::PHASE: name = "phase"; break;
  case PowerLab::ModelDesign::ParameterType::TIME: name = "time"; break;
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

std::ostream& operator<<(std::ostream& out, const PowerLab::ModelDesign::ParameterType& type) {
  out << getStringName(type);
  return out;
}

namespace PowerLab {
namespace ModelDesign {

const std::string& parameterTypeToStr(ParameterType type) {
  return getStringName(type);
}

const std::string& parameterTypeUnitsToStr(ParameterType type) {
  return UNITS_MAP.at(type);
}

ElementParameter::~ElementParameter() { /* EMPTY */ }

ParameterType ElementParameter::getType() const {
  return ParameterType::QUANTITY;
}

const std::string& ElementParameter::getUnits() const {
  return UNITS_MAP.at(ElementParameter::getType());
}

void ElementParameter::getValueImpl(const double** pointer) const {
  static double INVALID_VALUE = std::numeric_limits<double>::quiet_NaN();
  *pointer = &INVALID_VALUE;
  Logger::log(Message::ERROR_ELEMENT_PARAMETER_DOESNT_SUPPORT_TYPE, parameterTypeToStr(getType()), "double");
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

const std::string& FloatElementParameter::getUnits() const {
  return ElementParameter::getUnits();
}

void FloatElementParameter::getValueImpl(const int** pointer) const {
  ElementParameter::getValueImpl(pointer);
}

void FloatElementParameter::setValueImpl(int value) {
  ElementParameter::setValueImpl(value);
}

void FloatElementParameter::getValueImpl(const std::string** pointer) const {
  ElementParameter::getValueImpl(pointer);
}

void FloatElementParameter::setValueImpl(const std::string& value) {
  ElementParameter::setValueImpl(value);
}

void FloatElementParameter::getValueImpl(const double** pointer) const {
  *pointer = &m_value;
}

void FloatElementParameter::setValueImpl(double value) {
  m_value = value;
}

void IntegerElementParameter::getValueImpl(const double** pointer) const {
  ElementParameter::getValueImpl(pointer);
}

void IntegerElementParameter::setValueImpl(double value) {
  ElementParameter::setValueImpl(value);
}

void IntegerElementParameter::getValueImpl(const std::string** pointer) const {
  ElementParameter::getValueImpl(pointer);
}

void IntegerElementParameter::setValueImpl(const std::string& value) {
  ElementParameter::setValueImpl(value);
}

void StringElementParameter::getValueImpl(const int** pointer) const {
  ElementParameter::getValueImpl(pointer);
}

void StringElementParameter::setValueImpl(int value) {
  ElementParameter::setValueImpl(value);
}

void StringElementParameter::getValueImpl(const double** pointer) const {
  ElementParameter::getValueImpl(pointer);
}

void StringElementParameter::setValueImpl(double value) {
  ElementParameter::setValueImpl(value);
}

} // namespace ModelDesign
} // namespace PowerLab
