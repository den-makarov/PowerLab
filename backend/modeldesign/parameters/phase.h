#ifndef PHASE_H
#define PHASE_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Phase : public FloatElementParameter {
public:
  Phase(double value = 0.0);
  virtual ~Phase() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // PHASE_H
