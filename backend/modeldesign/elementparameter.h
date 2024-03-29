#ifndef ELEMENTPARAMETER_H
#define ELEMENTPARAMETER_H

#include <string>
#include <map>
#include <memory>
#include <vector>
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
  STATE,
};

using ParameterName = std::string;

class ElementParameter {
public:
  virtual ~ElementParameter();

  virtual ParameterType getType() const = 0;
  virtual ParameterName getName() const;
  virtual const std::string& getUnits() const;

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
  ElementParameter() = default;

  virtual void getValueImpl(const double** pointer) const = 0;
  virtual void setValueImpl(double value) = 0;

  virtual void getValueImpl(const int** pointer) const = 0;
  virtual void setValueImpl(int value) = 0;

  virtual void getValueImpl(const std::string** pointer) const = 0;
  virtual void setValueImpl(const std::string& value) = 0;
};

class ElementParameterMap {
public:
  ElementParameterMap() = default;

  void addParameter(const ParameterName& name, std::unique_ptr<ElementParameter>&& parameter);
  void addParameter(const ParameterType& name, std::unique_ptr<ElementParameter>&& parameter);

  const ElementParameter* getParameter(const std::string& name) const;
  ElementParameter* getParameter(const std::string& name);

  const ElementParameter* getParameter(const ParameterType& type) const;
  ElementParameter* getParameter(const ParameterType& type);

  std::vector<const ElementParameter*> getAllParameters() const;

private:
  std::map<ParameterName, std::unique_ptr<ElementParameter>> m_parameters;
};

class FloatElementParameter : public ElementParameter {
public:
  virtual ~FloatElementParameter() override = default;

protected:
  explicit FloatElementParameter(double value)
    : m_value(value)
  {}

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
  virtual ~IntegerElementParameter() override = default;

protected:
  explicit IntegerElementParameter(int value)
    : m_value(value)
  {}

  virtual void getValueImpl(const int** pointer) const override;
  virtual void setValueImpl(int value) override;

private:
  virtual void getValueImpl(const std::string** pointer) const override;
  virtual void setValueImpl(const std::string& value) override;
  virtual void getValueImpl(const double** pointer) const override;
  virtual void setValueImpl(double value) override;

  int m_value;
};

class StateElementParameter : public IntegerElementParameter {
public:
  virtual ~StateElementParameter() override = default;

protected:
  explicit StateElementParameter(int value)
    : IntegerElementParameter(value)
  {}

private:
  virtual void setValueImpl(int value) override;
};

class StringElementParameter : public ElementParameter {
public:
  virtual ~StringElementParameter() override = default;

protected:
  StringElementParameter() = default;

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
