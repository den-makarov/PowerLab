#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <map>
#include <memory>
#include <set>

#include "modeldesign/elementconnectionmanager.h"
#include "modeldesign/circuitelement.h"

namespace PowerLab {
namespace ModelDesign {

class Model {
public:
  Model(const std::string& name);

  std::vector<Connection> getConnections();
  void addConnection(Connection connection);

  std::vector<Element> getElements();
  Element getElement(const std::string& name);
  void addElement(Element element);

private:
  std::string m_name;
  std::map<std::string, Element> m_elements;
  std::set<Connection> m_connections;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // MODEL_H
