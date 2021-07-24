#include "elementconnectionmanager.h"

namespace PowerLab {
namespace ModelDesign {

ConnectionId ElementConnectionManager::m_connectionCounter = 0;

ElementConnectionManager::ElementConnectionManager() {
  m_connectionCounter = 0;
}

ConnectionId ElementConnectionManager::createConnection() {
  m_connectionCounter++;
  m_connections.insert({m_connectionCounter, std::make_unique<ElementConnection>(m_connectionCounter)});
  return m_connectionCounter;
}

void ElementConnectionManager::destroyConnection(ConnectionId id) {
  auto connection = m_connections.find(id);
  if(connection != m_connections.end()) {
    m_connections.erase(connection);
  }
}

} // namespace ModelDesign
} // namespace PowerLab
