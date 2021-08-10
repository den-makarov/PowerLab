#ifndef ELEMENTPORT_H
#define ELEMENTPORT_H

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <functional>

#include "elementconnection.h"

namespace PowerLab {
namespace ModelDesign {

enum class PortType {
  POWER_IN,
  POWER_OUT,
  CONTROL_IN,
  CONTROL_OUT,
  GENERAL_PURPOSE_IN,
  GENERAL_PURPOSE_OUT,
  GENERAL_PURPOSE,
};

using PortNumber = size_t;

class CircuitElement;

class ElementPort;
using Port = std::shared_ptr<ElementPort>;
using CPort = std::shared_ptr<const ElementPort>;

class ElementPort {
public:
  static Port createPort(const CircuitElement& owner, PortType type);
  explicit ElementPort(const CircuitElement& owner, PortType type);

  void connect(Connection connection);
  void disconnect();
  bool isConnected() const;
  Connection getConnection() const;
  std::string getOwnerName() const;
  PortType getType() const;
  void setType(PortType type);

private:
  Connection m_connection;
  const CircuitElement& m_owner;
  PortType m_type;
};

class ElementPortMap {
public:
  ElementPortMap() = default;

  size_t getPortCount() const;

  std::vector<CPort> getAllPorts() const;
  std::vector<Port> getAllPorts();

  CPort getPort(PortNumber number) const;
  Port getPort(PortNumber number);

  std::vector<CPort> getPortsOfType(PortType type) const;
  std::vector<Port> getPortsOfType(PortType type);

  void addPort(Port port);

private:
  std::vector<Port> m_ports;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTPORT_H
