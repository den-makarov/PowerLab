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
  m_parameters[name] = std::move(parameter);
}

void CircuitElement::addParameter(const ParameterType& name, std::unique_ptr<ElementParameter>&& parameter) {
  addParameter(parameterTypeToStr(name), std::move(parameter));
}

const ElementParameter* CircuitElement::getParameter(const std::string& name) const {
  auto it = m_parameters.find(name);
  if(it != m_parameters.end()) {
    return it->second.get();
  } else {
    return nullptr;
  }
}

ElementParameter* CircuitElement::getParameter(const std::string& name) {
  auto it = m_parameters.find(name);
  if(it != m_parameters.end()) {
    return it->second.get();
  } else {
    return nullptr;
  }
}

const ElementParameter* CircuitElement::getParameter(const ParameterType& type) const {
  return getParameter(parameterTypeToStr(type));
}

ElementParameter* CircuitElement::getParameter(const ParameterType& type) {
  return getParameter(parameterTypeToStr(type));
}

std::vector<const ElementParameter*> CircuitElement::getAllParameters() const {
  std::vector<const ElementParameter*> result;
  for(auto&& [name, param] : m_parameters) {
    result.push_back(param.get());
  }

  return result;
}

} // namespace ModelDesign
} // namespace PowerLab
