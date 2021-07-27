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

    const T** pointer;
    getValue(pointer);
    return **pointer;
  }

  template<typename T>
  void setValue(const T& value) {
    constexpr bool supportedType = std::is_same<T, std::string>::value
                                || std::is_same<T, int>::value
                                || std::is_same<T, double>::value;
    static_assert(supportedType, "Parameter type isn't supported");

    setValue(value);
  }

protected:
  virtual void getValue(const double** pointer) const = 0;
  virtual void setValue(double value) = 0;

  virtual void getValue(const int** pointer) const = 0;
  virtual void setValue(int pointer) = 0;

  virtual void getValue(const std::string** pointer) const = 0;
  virtual void setValue(const std::string& pointer) = 0;

private:
  const std::string m_name;
};

class Resistance : public ElementParameter {
public:
  Resistance(const std::string& name, double value = 1.0);
  virtual ~Resistance() override = default;

  virtual ParameterType getType() const override;
  virtual const std::string& getUnits() const override;

private:
  virtual void getValue(const double** pointer) const override;
  virtual void setValue(double value) override;

  virtual void getValue(const int** pointer) const override;
  virtual void setValue(int value) override;

  virtual void getValue(const std::string** pointer) const override;
  virtual void setValue(const std::string& value) override;

  double m_value;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTPARAMETER_H
