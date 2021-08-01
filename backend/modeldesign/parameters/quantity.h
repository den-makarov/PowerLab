#ifndef QUANTITY_H
#define QUANTITY_H

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class Quantity : public FloatElementParameter {
public:
  Quantity(double value = 0.0);
  virtual ~Quantity() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // QUANTITY_H
