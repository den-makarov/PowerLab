#include "elementport.h"
#include "elementconnectionmanager.h"

namespace PowerLab {
namespace Model {

ElementPort::ElementPort(const AbstractElement& owner)
  : m_owner(owner)
{

}

void ElementPort::connect(ConnectionId connection) {
  m_connections.insert(connection);
}

void ElementPort::disconnect(ConnectionId connection) {
  m_connections.erase(connection);
}

bool ElementPort::isConnected(ConnectionId connection) const {
  return m_connections.find(connection) != m_connections.end();
}

} // namespace Model
} // namespace PowerLab
