#include "elementport.h"
#include "elementconnectionmanager.h"
#include "circuitelement.h"

namespace PowerLab {
namespace ModelDesign {

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

void ElementPortMap::addPort(std::unique_ptr<ElementPort>&& port) {
  m_ports.emplace_back(std::move(port));
}

std::vector<ElementPortCRef> ElementPortMap::getAllPorts() const {
  std::vector<ElementPortCRef> res;
  for(auto& pPort : m_ports) {
    res.push_back(std::cref(*pPort.get()));
  }
  return res;
}

std::vector<ElementPortRef> ElementPortMap::getAllPorts() {
  std::vector<ElementPortRef> res;
  for(auto& pPort : m_ports) {
    res.push_back(std::ref(*pPort.get()));
  }
  return res;
}

const ElementPort* ElementPortMap::getPort(PortNumber number) const {
  return number <= m_ports.size() ? m_ports[number].get() : nullptr;
}

ElementPort* ElementPortMap::getPort(PortNumber number) {
  return number <= m_ports.size() ? m_ports[number].get() : nullptr;
}

std::vector<ElementPortCRef> ElementPortMap::getPortsOfType(PortType type) const {
  std::vector<ElementPortCRef> res;
  for(auto& pPort : m_ports) {
    auto& port = *pPort.get();
    if(port.getType() == type) {
      res.push_back(std::cref(*pPort.get()));
    }
  }
  return res;
}

std::vector<ElementPortRef> ElementPortMap::getPortsOfType(PortType type) {
  std::vector<ElementPortRef> res;
  for(auto& pPort : m_ports) {
    auto& port = *pPort.get();
    if(port.getType() == type) {
      res.push_back(std::ref(*pPort.get()));
    }
  }
  return res;
}

} // namespace ModelDesign
} // namespace PowerLab
