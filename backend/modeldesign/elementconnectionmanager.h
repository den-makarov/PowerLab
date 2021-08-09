#ifndef ELEMENTCONNECTIONMANAGER_H
#define ELEMENTCONNECTIONMANAGER_H

#include <map>
#include <memory>

#include "elementconnection.h"

namespace PowerLab {
namespace ModelDesign {

class ElementConnectionManager {
public:
  ElementConnectionManager();

  ElementConnectionManager(const ElementConnectionManager& manager) = delete;
  ElementConnectionManager& operator=(const ElementConnectionManager& manager) = delete;

private:
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTCONNECTIONMANAGER_H
