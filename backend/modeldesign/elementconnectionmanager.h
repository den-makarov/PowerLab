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

  ConnectionId createConnection();
  void destroyConnection(ConnectionId);

  ElementConnection* getConnection(ConnectionId id);
  const ElementConnection* getConnection(ConnectionId id) const;

private:
  std::map<ConnectionId, std::unique_ptr<ElementConnection>> m_connections;

  static ConnectionId m_connectionCounter;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTCONNECTIONMANAGER_H
