#include "circuitelement.h"
#include "elementconnectionmanager.h"

namespace PowerLab {
namespace ModelDesign {

CircuitElement::CircuitElement(const ElementName& name)
  : m_name(name)
{

}

CircuitElement::~CircuitElement() {
  for(auto port : getAllPorts()) {
    if(port.get().isConnected()) {
      Connection c(port.get().getConnection());
      c.disconnectPort(port);
    }
  }
}

void CircuitElement::updateName(const ElementName& name) {
  m_name = name;
}

const CircuitElement::ElementName& CircuitElement::getName() const {
  return m_name;
}

void CircuitElement::addPort(std::unique_ptr<ElementPort>&& port) {
  m_ports.addPort(std::move(port));
}

void CircuitElement::addChild(std::unique_ptr<CircuitElement>&& child) {
  m_children.emplace_back(std::move(child));
}

std::vector<const ElementParameter*> CircuitElement::getAllParameters() const {
  return m_parameters.getAllParameters();
}

std::vector<ElementPortCRef> CircuitElement::getAllPorts() const {
  return m_ports.getAllPorts();
}

std::vector<ElementPortRef> CircuitElement::getAllPorts() {
  return m_ports.getAllPorts();
}

} // namespace ModelDesign
} // namespace PowerLab
