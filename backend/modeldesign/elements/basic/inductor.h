#ifndef INDUCTOR_H
#define INDUCTOR_H

// Inductor description:
// LYYYYYYY n+ n- <value> <mname> <nt=val> <temperature model> <ic=init_condition>
// Explanation:
// n+ & n- - two nodes
// value - inductance in Henry. Lnom
// mname - model name. See model description
// nt - number of turns
// ic - initial current value in ampheres
//
// .MODEL description:
// IND - inductance in [H]. Default 0.0
// CSECT - effective cross section [m^2]. Default 0.0
// LENGTH - effective core lenght [m]. Default 0.0
// TNOM - parameter measurement temperature. Default 27
// NT - number of turns (nt parameter in instance description overrides .model parameter)
// MU - relative magnetic permeability [h/m]
// if value or IND are not set, inductance is calculated by:
// Lnom = MU * u0 * NT^2 * CSECT / LENGTH

#include "modeldesign/circuitelement.h"

namespace PowerLab {
namespace ModelDesign {

class Inductor : public CircuitElement {
public:
  Inductor(const ElementName& name);
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // INDUCTOR_H
