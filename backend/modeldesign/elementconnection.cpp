#include <algorithm>
#include <sstream>

#include "elementconnection.h"
#include "elementport.h"
#include "elementconnectionmanager.h"
#include "logger.h"

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

bool Connection::isValid(ConnectionId id) {
  return id != INVALID_CONNECTION;
}

Connection::Connection(ConnectionId id)
  : m_id(id)
{
}

bool Connection::isExist() const {
  if(isValid(m_id) && ElementConnectionManager::instance().getConnection(m_id) != nullptr) {
    return true;
  }

  Logger::log(Message::ERROR_INVALID_CONNECTION, m_id);
  return false;
}

void Connection::setUserName(const std::string& name) {
  if(isExist()) {
    auto connection = ElementConnectionManager::instance().getConnection(m_id);
    connection->setUserName(name);
  }
}

std::string Connection::getUserName() const {
  if(isExist()) {
    auto connection = ElementConnectionManager::instance().getConnection(m_id);
    return connection->getUserName();
  }
  return "";
}

void Connection::connectPort(ElementPort* port) {
  if(isExist() && port != nullptr) {
    auto connection = ElementConnectionManager::instance().getConnection(m_id);
    connection->connectPort(port);
  }
}

void Connection::disconnectPort(ElementPort* port) {
  if(isExist() && port != nullptr) {
    auto connection = ElementConnectionManager::instance().getConnection(m_id);
    connection->disconnectPort(port);
  }
}

bool Connection::isConnectedPort(const ElementPort* port) const {
  if(isExist() && port != nullptr) {
    auto connection = ElementConnectionManager::instance().getConnection(m_id);
    return connection->isConnectedPort(port);
  }

  return false;
}

std::string Connection::getModel() const {
  if(isExist()) {
    auto connection = ElementConnectionManager::instance().getConnection(m_id);
    return connection->getModel();
  }
  return "";
}

std::string Connection::str() const {
  if(isExist()) {
    auto connection = ElementConnectionManager::instance().getConnection(m_id);
    return connection->str();
  }
  return "";
}

} // namespace ModelDesign
} // namespace PowerLab
