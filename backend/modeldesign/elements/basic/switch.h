#ifndef SWITCH_H
#define SWITCH_H

#include "modeldesign/abstractelement.h"

namespace PowerLab {
namespace ModelDesign {

class Switch : public AbstractElement {
public:
  Switch(const ElementName& name);
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // SWITCH_H
