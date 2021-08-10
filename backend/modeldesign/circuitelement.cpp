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
    port->disconnect();
  }
}

void CircuitElement::updateName(const ElementName& name) {
  m_name = name;
}

const CircuitElement::ElementName& CircuitElement::getName() const {
  return m_name;
}

void CircuitElement::addPort(Port port) {
  m_ports.addPort(std::move(port));
}

void CircuitElement::addChild(std::unique_ptr<CircuitElement>&& child) {
  m_children.emplace_back(std::move(child));
}

std::vector<const ElementParameter*> CircuitElement::getAllParameters() const {
  return m_parameters.getAllParameters();
}

std::vector<CPort> CircuitElement::getAllPorts() const {
  return m_ports.getAllPorts();
}

std::vector<Port> CircuitElement::getAllPorts() {
  return m_ports.getAllPorts();
}

std::vector<CPort> CircuitElement::getPortsOfType(PortType type) const {
  return m_ports.getPortsOfType(type);
}

std::vector<Port> CircuitElement::getPortsOfType(PortType type) {
  return m_ports.getPortsOfType(type);
}

std::ostream& CircuitElement::getConnectionModel(std::ostream& out, CPort port) const {
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
