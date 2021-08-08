#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <map>
#include <memory>

#include "modeldesign/elementconnectionmanager.h"
#include "modeldesign/circuitelement.h"

namespace PowerLab {
namespace ModelDesign {

class Model {
public:
  Model(const std::string& name);
private:
  std::string m_name;
  std::map<std::string, std::unique_ptr<CircuitElement>> m_elements;
  std::unique_ptr<ElementConnectionManager> m_connectionManager;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // MODEL_H
