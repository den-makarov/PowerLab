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

std::vector<const ElementParameter*> CircuitElement::getAllParameters() const {
  return m_parameters.getAllParameters();
}

std::vector<const ElementPort*> CircuitElement::getAllPorts() const {
  std::vector<const ElementPort*> result;
  for(auto& port : m_ports) {
    result.push_back(port.get());
  }

  return result;
}

std::vector<ElementPort*> CircuitElement::getAllPorts() {
  std::vector<ElementPort*> result;
  for(auto& port : m_ports) {
    result.push_back(port.get());
  }

  return result;
}

} // namespace ModelDesign
} // namespace PowerLab
