#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Resistance : public DoubleElementParameter {
public:
  Resistance(double value = 1.0);
  virtual ~Resistance() override = default;

  virtual ParameterType getType() const override;
  virtual const std::string& getUnits() const override;

private:
  virtual void getValueImpl(const double** pointer) const override;
  virtual void setValueImpl(double value) override;

  double m_value;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // RESISTANCE_H
