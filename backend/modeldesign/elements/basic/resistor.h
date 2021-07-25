#ifndef RESISTOR_H
#define RESISTOR_H

#include "modeldesign/abstractelement.h"

namespace PowerLab {
namespace ModelDesign {

class Resistor : public AbstractElement {
public:
  Resistor(const ElementName& name);
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // RESISTOR_H
