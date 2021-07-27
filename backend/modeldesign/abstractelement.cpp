#include "abstractelement.h"

namespace PowerLab {
namespace ModelDesign {

CircuitElement::CircuitElement(const ElementName& name)
  : m_name(name)
{

}

void CircuitElement::updateName(const ElementName& name) {
  m_name = name;
}

const CircuitElement::ElementName& CircuitElement::getName() const {
  return m_name;
}

void CircuitElement::addPort(std::unique_ptr<ElementPort>&& port) {
  m_ports.emplace_back(std::move(port));
}

void CircuitElement::addChild(std::unique_ptr<CircuitElement>&& child) {
  m_children.emplace_back(std::move(child));
}

void CircuitElement::addParameter(const ParameterName& name, std::unique_ptr<ElementParameter>&& parameter) {
  m_parameters.emplace(name, std::move(parameter));
}

} // namespace ModelDesign
} // namespace PowerLab
