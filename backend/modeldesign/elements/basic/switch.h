#ifndef SWITCH_H
#define SWITCH_H

// Voltage controlled switch description:
// SXXXXXXXX n+ n- nc+ nc- ModelName [OFF|ON]
// .model ModelName sw vt= vh= ron= roff=
// n+ n- - node names
// nc+ nc- - control node names
// [OFF|ON] - optional initial state
// vt= - voltage threshold [V]. Default 0.0
// vh= - voltage hysteresis [V]. Default 0.0
// ron= - on resistance. Deafult 1 Ohm
// roff= - off resistance. Deafult 1.0e+12 Ohm

#include "modeldesign/abstractelement.h"

namespace PowerLab {
namespace ModelDesign {

class Switch : public AbstractElement {
public:
  Switch(const ElementName& name);
private:
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // SWITCH_H
