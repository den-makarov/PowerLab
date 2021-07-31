#ifndef VOLTAGE_H
#define VOLTAGE_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Voltage : public FloatElementParameter {
public:
  Voltage(double value = 1.0);
  virtual ~Voltage() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // VOLTAGE_H
