#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "modeldesign/abstractelement.h"

namespace PowerLab {
namespace ModelDesign {

class Inductor : public AbstractElement {
public:
  Inductor(const ElementName& name);
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // INDUCTOR_H
