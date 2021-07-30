#ifndef INDUCTANCE_H
#define INDUCTANCE_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Inductance : public FloatElementParameter {
public:
  Inductance(double value = 0.001);
  virtual ~Inductance() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // INDUCTANCE_H
