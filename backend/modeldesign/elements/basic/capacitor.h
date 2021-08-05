#ifndef CAPACITOR_H
#define CAPACITOR_H

// CXXXXXXX n+ n- <value> <mname> <temperature model> <ic=init_condition>
// n+ n- - node names
// value - capacitance in Farads. Cnom
// mname - model name. See model description
// ic - initial voltage [V]

// .MODEL description:
// CAP - capacitance [F]. Default 0.0
// CJ - junction bottom capacitance [F/m^2]
// CJSW - junction sidewall capacitance [F/m]
// DEFW - default device width [m]. Default 1e-6
// DEFL - default device length [m]. Default 1e-6
// NARROW - narrowing due to side etching [m]. Default 0.0
// SHORT - shortening due to side etching [m]. Default 0.0
// TNOM - parameter measurement temperature. Default 27
// DI - relative dielectric constant [F/m]
// THICK - insulator thickness [m]. Default 0.0

// Cnom = CJ * (l − SHORT) * (w − NARROW) + 2 * CJSW * (l − SHORT + w − NARROW)
// if CJ isn't provided, it is calculated:
// CJ = DI * e0 / THICK if DI is specified, otherwise CJ = e(SiO2) / THICK
// where e0 = 8.854214871e−12 [F/m], e(SiO2) = 3.4531479969e−11 [F/m]

#include "modeldesign/circuitelement.h"

namespace PowerLab {
namespace ModelDesign {

class Capacitor : public CircuitElement {
public:
  Capacitor(const ElementName& name);
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // CAPACITOR_H
