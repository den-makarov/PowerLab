#include "abstractelement.h"

namespace PowerLab {
namespace Model {

AbstractElement::AbstractElement(const ElementName& name)
  : m_name(name)
{

}

const AbstractElement::ElementName& AbstractElement::getName() const {
  return m_name;
}

} // namespace Model
} // namespace PowerLab
