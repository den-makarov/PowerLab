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
    port.get().disconnect();
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

std::vector<ElementPortCRef> CircuitElement::getPortsOfType(PortType type) const {
  return m_ports.getPortsOfType(type);
}

std::vector<ElementPortRef> CircuitElement::getPortsOfType(PortType type) {
  return m_ports.getPortsOfType(type);
}

std::ostream& CircuitElement::getConnectionModel(std::ostream& out, const ElementPort* port) const {
  if(port) {
    auto connection = port->getConnection();
    if(connection) {
      out << connection->getModel();
    } else {
      out << "NC";
    }
  } else {
    out << "NC";
  }
  return out;
}

} // namespace ModelDesign
} // namespace PowerLab
