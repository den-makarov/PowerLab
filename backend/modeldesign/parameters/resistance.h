#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Resistance : public FloatElementParameter {
public:
  Resistance(double value = 1.0);
  virtual ~Resistance() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // RESISTANCE_H
