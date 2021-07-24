#include <algorithm>

#include "elementconnection.h"
#include "elementport.h"

namespace PowerLab {
namespace Model {

ElementConnection::ElementConnection(ConnectionId id)
  : m_id(id)
{
}

ElementConnection::~ElementConnection() {
  for(auto& p : m_connectedPorts) {
    p->disconnect(m_id);
  }
}

void ElementConnection::connectPort(ElementPort* port) {
  auto connected = isConnectedPort(port);
  if(!connected) {
    m_connectedPorts.push_back(port);
  }
}

void ElementConnection::disconnectPort(ElementPort* port) {
  auto connectedPort = std::find(m_connectedPorts.begin(), m_connectedPorts.end(), port);
  if(connectedPort != m_connectedPorts.end()) {
    m_connectedPorts.erase(connectedPort);
  }
}

bool ElementConnection::isConnectedPort(const ElementPort* port) const {
  return std::find(m_connectedPorts.begin(), m_connectedPorts.end(), port) != m_connectedPorts.end();
}

} // namespace Model
} // namespace PowerLab
