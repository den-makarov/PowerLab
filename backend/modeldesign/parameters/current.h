#ifndef CURRENT_H
#define CURRENT_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Current : public FloatElementParameter {
public:
  Current(double value = 1.0);
  virtual ~Current() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // CURRENT_H
