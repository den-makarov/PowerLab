#ifndef FREQUENCY_H
#define FREQUENCY_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Frequency : public FloatElementParameter {
public:
  Frequency(double value = 1.0);
  virtual ~Frequency() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // FREQUENCY_H
