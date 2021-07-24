#ifndef ELEMENTPARAMETER_H
#define ELEMENTPARAMETER_H

#include <variant>
#include <string>

namespace PowerLab {
namespace ModelDesign {

using ElementParameter = std::variant<int, double, std::string>;

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTPARAMETER_H
