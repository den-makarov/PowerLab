#include <algorithm>
#include <sstream>

#include "elementconnection.h"
#include "elementport.h"
#include "elementconnectionmanager.h"
#include "logger.h"

namespace PowerLab {
namespace ModelDesign {

Connection ElementConnection::createConnection() {
  return std::make_shared<ElementConnection>();
}

ElementConnection::ConnectionId ElementConnection::globalId = 0;

ElementConnection::ElementConnection()
  : m_id(globalId++)
{
}

ElementConnection::~ElementConnection() {
//  for(auto& p : m_connectedPorts) {
//    p->disconnect();
//  }
}

void ElementConnection::connectPort(ElementPort& port) {
  auto connected = isConnectedPort(port);
  if(!connected) {
    m_connectedPorts.push_back(&port);
  }
}

void ElementConnection::disconnectPort(ElementPort& port) {
  auto connectedPort = std::find(m_connectedPorts.begin(), m_connectedPorts.end(), &port);
  if(connectedPort != m_connectedPorts.end()) {
    m_connectedPorts.erase(connectedPort);
    port.disconnect();
  }
}

bool ElementConnection::isConnectedPort(const ElementPort& port) const {
  return std::find(m_connectedPorts.begin(), m_connectedPorts.end(), &port) != m_connectedPorts.end();
}

void ElementConnection::setUserName(const std::string& name) {
  m_userName = name;
}

const std::string& ElementConnection::getUserName() const {
  return m_userName;
}

std::string ElementConnection::getModel() const {
  return std::to_string(m_id);
}

std::string ElementConnection::str() const {
  std::ostringstream str;

  str << "Connection: " << getModel();
  if(!m_userName.empty()) {
    str << " User name: " << m_userName;
  }

  str << " Connected elements: {";
  if(!m_connectedPorts.empty()) {
    auto it = m_connectedPorts.begin();
    str << (*it++)->getOwnerName();
    while(it != m_connectedPorts.end()) {
      str << ", " << (*it++)->getOwnerName();
    }
  }
  str << "}";

  return str.str();
}

} // namespace ModelDesign
} // namespace PowerLab
