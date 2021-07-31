#ifndef ELEMENTPARAMETER_H
#define ELEMENTPARAMETER_H

#include <variant>
#include <string>
#include <iostream>

namespace PowerLab {
namespace ModelDesign {

enum class ParameterType {
  RESISTANCE,
  INDUCTANCE,
  CAPACITANCE,
  VOLTAGE,
  CURRENT,
  FREQUENCY,
  PERIOD,
  PHASE,
  TIME,
  TEMPERATURE,
  LENGTH,
  WIDTH,
  AREA,
  VOLUME,
  QUANTITY,
  STATE
};

class ElementParameter {
public:
  ElementParameter() = default;
  virtual ~ElementParameter();

  virtual ParameterType getType() const = 0;
  virtual const std::string& getUnits() const = 0;

  template<typename T>
  const auto& getValue() const {
    constexpr bool supportedType = std::is_same<T, std::string>::value
                                || std::is_same<T, int>::value
                                || std::is_same<T, double>::value;
    static_assert(supportedType, "Parameter type isn't supported");

    const T* pointer = nullptr;
    getValueImpl(&pointer);
    return *pointer;
  }

  template<typename T>
  void setValue(const T& value) {
    constexpr bool supportedType = std::is_same<T, std::string>::value
                                || std::is_same<T, int>::value
                                || std::is_same<T, double>::value;
    static_assert(supportedType, "Parameter type isn't supported");

    setValueImpl(value);
  }

protected:
  virtual void getValueImpl(const double** pointer) const = 0;
  virtual void setValueImpl(double value) = 0;

  virtual void getValueImpl(const int** pointer) const = 0;
  virtual void setValueImpl(int value) = 0;

  virtual void getValueImpl(const std::string** pointer) const = 0;
  virtual void setValueImpl(const std::string& value) = 0;
};

class FloatElementParameter : public ElementParameter {
public:
  explicit FloatElementParameter(double value)
    : m_value(value)
  {}
  virtual ~FloatElementParameter() override = default;

  virtual const std::string& getUnits() const override;

private:
  virtual void getValueImpl(const int** pointer) const override;
  virtual void setValueImpl(int value) override;
  virtual void getValueImpl(const std::string** pointer) const override;
  virtual void setValueImpl(const std::string& value) override;
  virtual void getValueImpl(const double** pointer) const override;
  virtual void setValueImpl(double value) override;

  double m_value;
};

class IntegerElementParameter : public ElementParameter {
public:
  explicit IntegerElementParameter(int value)
    : m_value(value)
  {}
  virtual ~IntegerElementParameter() override = default;

  virtual const std::string& getUnits() const override;

protected:
  virtual void setValueImpl(int value) override;
  virtual void getValueImpl(const int** pointer) const override;

private:
  virtual void getValueImpl(const std::string** pointer) const override;
  virtual void setValueImpl(const std::string& value) override;
  virtual void getValueImpl(const double** pointer) const override;
  virtual void setValueImpl(double value) override;

  int m_value;
};

class StateElementParameter : public IntegerElementParameter {
public:
  explicit StateElementParameter(int value)
    : IntegerElementParameter(value)
  {}
  virtual ~StateElementParameter() override = default;
private:
  virtual void setValueImpl(int value) override;
};

class StringElementParameter : public ElementParameter {
public:
  StringElementParameter() = default;
  virtual ~StringElementParameter() override = default;

  virtual const std::string& getUnits() const override;
private:
  virtual void getValueImpl(const int** pointer) const override;
  virtual void setValueImpl(int value) override;
  virtual void getValueImpl(const double** pointer) const override;
  virtual void setValueImpl(double value) override;

protected:
  virtual void getValueImpl(const std::string** pointer) const override = 0;
  virtual void setValueImpl(const std::string& value) override = 0;
};

const std::string& parameterTypeToStr(ParameterType type);
const std::string& parameterTypeUnitsToStr(ParameterType type);

} // namespace ModelDesign
} // namespace PowerLab

std::ostream& operator<<(std::ostream& out, const PowerLab::ModelDesign::ParameterType& type);

#endif // ELEMENTPARAMETER_H
