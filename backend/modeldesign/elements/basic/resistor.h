#ifndef RESISTOR_H
#define RESISTOR_H

// RXXXXXXX n+ n- value <ac=val> <temperature model> <noisy=0|1>
// n+ n- - node names
// value - resistance [Ohm]. Rnom
// ac - resistance used in AC analysis
// noisy - temperature and flicker noise simulation

#include "modeldesign/circuitelement.h"

namespace PowerLab {
namespace ModelDesign {

class Resistor : public CircuitElement {
public:
  Resistor(const ElementName& name);
  virtual std::string getModel() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // RESISTOR_H
