#ifndef ELEMENTCONNECTIONMANAGER_H
#define ELEMENTCONNECTIONMANAGER_H

#include <map>
#include <memory>

#include "elementconnection.h"

namespace PowerLab {
namespace Model {

class ElementConnectionManager {
public:
  static ElementConnectionManager& instance() {
    static ElementConnectionManager _;
    return _;
  }

  ElementConnectionManager(const ElementConnectionManager& manager) = delete;
  ElementConnectionManager& operator=(const ElementConnectionManager& manager) = delete;
  ElementConnectionManager(ElementConnectionManager&& manager) = delete;
  ElementConnectionManager& operator=(ElementConnectionManager&& manager) = delete;

  ConnectionId createConnection();
  void destroyConnection(ConnectionId);

private:
  ElementConnectionManager();

  std::map<ConnectionId, std::unique_ptr<ElementConnection>> m_connections;

  static ConnectionId connectionCounter;
};

} // namespace Model
} // namespace PowerLab

#endif // ELEMENTCONNECTIONMANAGER_H
