#ifndef ELEMENTPARAMETER_H
#define ELEMENTPARAMETER_H

#include <variant>
#include <string>

namespace PowerLab {
namespace ModelDesign {

enum class ParameterType {
  RESISTANCE,
  INDUCTANCE,
  CAPACITANCE,
  VOLTAGE,
  CURRENT,
  TEMPERATURE,
  LENGTH,
  WIDTH,
  AREA,
  VOLUME,
  QUANTITY
};

class ElementParameter {
public:
  explicit ElementParameter(const std::string& name);
  virtual ~ElementParameter() = default;

  const std::string& getName() const;
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

private:
  const std::string m_name;
};

class DoubleElementParameter : public ElementParameter {
public:
  explicit DoubleElementParameter(const std::string& name)
    : ElementParameter(name) {}
  virtual ~DoubleElementParameter() override = default;

private:
  virtual void getValueImpl(const int** pointer) const override {
    ElementParameter::getValueImpl(pointer);
  }

  virtual void setValueImpl(int value) override {
    ElementParameter::setValueImpl(value);
  }

  virtual void getValueImpl(const std::string** pointer) const override {
    ElementParameter::getValueImpl(pointer);
  }

  virtual void setValueImpl(const std::string& value) override {
    ElementParameter::setValueImpl(value);
  }

protected:
  virtual void getValueImpl(const double** pointer) const override = 0;
  virtual void setValueImpl(double value) override = 0;
};

const std::string& parameterTypeToString(ParameterType type);
const std::string& parameterTypeUnits(ParameterType type);

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTPARAMETER_H
