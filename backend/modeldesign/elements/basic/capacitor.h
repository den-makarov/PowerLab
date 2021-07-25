#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "modeldesign/abstractelement.h"

namespace PowerLab {
namespace ModelDesign {

class Capacitor : public AbstractElement {
public:
  Capacitor(const ElementName& name);
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // CAPACITOR_H
