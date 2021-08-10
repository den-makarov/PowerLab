#include "elementport.h"
#include "elementconnectionmanager.h"
#include "circuitelement.h"

namespace PowerLab {
namespace ModelDesign {

Port ElementPort::createPort(const CircuitElement& owner, PortType type) {
  return std::make_shared<ElementPort>(owner, type);
}

ElementPort::ElementPort(const CircuitElement& owner, PortType type)
  : m_owner(owner)
  , m_type(type)
{
}

void ElementPort::connect(Connection connection) {
  m_connection = connection;
  m_connection->connectPort(*this);
}

void ElementPort::disconnect() {
  m_connection.reset();
}

bool ElementPort::isConnected() const {
  return m_connection != nullptr;
}

Connection ElementPort::getConnection() const {
  return m_connection;
}

std::string ElementPort::getOwnerName() const {
  return m_owner.getName();
}

PortType ElementPort::getType() const {
  return m_type;
}

void ElementPort::setType(PortType type) {
  m_type = type;
}

size_t ElementPortMap::getPortCount() const {
  return m_ports.size();
}

void ElementPortMap::addPort(Port port) {
  m_ports.emplace_back(port);
}

std::vector<CPort> ElementPortMap::getAllPorts() const {
  std::vector<CPort> res;
  for(const auto& port : m_ports) {
    res.push_back(port);
  }
  return res;
}

std::vector<Port> ElementPortMap::getAllPorts() {
  std::vector<Port> res;
  for(auto& port : m_ports) {
    res.push_back(port);
  }
  return res;
}

CPort ElementPortMap::getPort(PortNumber number) const {
  return number <= m_ports.size() ? m_ports[number] : nullptr;
}

Port ElementPortMap::getPort(PortNumber number) {
  return number <= m_ports.size() ? m_ports[number] : nullptr;
}

std::vector<CPort> ElementPortMap::getPortsOfType(PortType type) const {
  std::vector<CPort> res;
  for(const auto& port : m_ports) {
    if(port->getType() == type) {
      res.push_back(port);
    }
  }
  return res;
}

std::vector<Port> ElementPortMap::getPortsOfType(PortType type) {
  std::vector<Port> res;
  for(auto& port : m_ports) {
    if(port->getType() == type) {
      res.push_back(port);
    }
  }
  return res;
}

} // namespace ModelDesign
} // namespace PowerLab
