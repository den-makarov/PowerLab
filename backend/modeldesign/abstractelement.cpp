#include "abstractelement.h"

namespace PowerLab {
namespace ModelDesign {

AbstractElement::AbstractElement(const ElementName& name)
  : m_name(name)
{

}

const AbstractElement::ElementName& AbstractElement::getName() const {
  return m_name;
}

void AbstractElement::addPort(std::unique_ptr<ElementPort>&& port) {
  m_ports.emplace_back(std::move(port));
}

void AbstractElement::addChild(std::unique_ptr<AbstractElement>&& child) {
  m_children.emplace_back(std::move(child));
}

void AbstractElement::addParameter(const ParameterName& name, std::unique_ptr<ElementParameter>&& parameter) {
  m_parameters.emplace(name, std::move(parameter));
}

} // namespace ModelDesign
} // namespace PowerLab
