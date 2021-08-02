#ifndef ELEMENTCONNECTIONMANAGER_H
#define ELEMENTCONNECTIONMANAGER_H

#include <map>
#include <memory>

#include "elementconnection.h"

namespace PowerLab {
namespace ModelDesign {

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

  ElementConnection* getConnection(ConnectionId id);
  const ElementConnection* getConnection(ConnectionId id) const;

private:
  ElementConnectionManager();

  std::map<ConnectionId, std::unique_ptr<ElementConnection>> m_connections;

  static ConnectionId m_connectionCounter;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTCONNECTIONMANAGER_H
