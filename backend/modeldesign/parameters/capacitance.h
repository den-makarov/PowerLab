#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Capacitance : public FloatElementParameter {
public:
  Capacitance(double value = 0.000001);
  virtual ~Capacitance() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // CAPACITANCE_H
