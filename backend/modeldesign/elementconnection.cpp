#include <algorithm>

#include "elementconnection.h"
#include "elementport.h"

namespace PowerLab {
namespace ModelDesign {

ElementConnection::ElementConnection(ConnectionId id)
  : m_id(id)
{
}

ElementConnection::~ElementConnection() {
  for(auto& p : m_connectedPorts) {
    p->disconnect();
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

void ElementConnection::setUserName(const std::string& name) {
  m_userName = name;
}

const std::string& ElementConnection::getUserName() const {
  return m_userName;
}

} // namespace ModelDesign
} // namespace PowerLab
