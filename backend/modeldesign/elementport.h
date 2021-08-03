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
  GENERAL_PURPOSE_BIDIR,
};

using PortNumber = size_t;

class CircuitElement;

class ElementPort {
public:
  explicit ElementPort(const CircuitElement& owner, PortType type);

  void connect(ConnectionId connection);
  void disconnect();
  bool isConnected() const;
  ConnectionId getConnection() const;
  std::string getOwnerName() const;
  PortType getType() const;
  void setType(PortType type);

private:
  ConnectionId m_connection = UNCONNECTED;
  const CircuitElement& m_owner;
  PortType m_type;
};

using ElementPortRef = std::reference_wrapper<ElementPort>;
using ElementPortCRef = std::reference_wrapper<const ElementPort>;

class ElementPortMap {
public:
  ElementPortMap() = default;

  size_t getPortCount() const;

  std::vector<ElementPortCRef> getAllPorts() const;
  std::vector<ElementPortRef> getAllPorts();

  const ElementPort* getPort(PortNumber number) const;
  ElementPort* getPort(PortNumber number);

  std::vector<ElementPortCRef> getPortsOfType(PortType type) const;
  std::vector<ElementPortRef> getPortsOfType(PortType type);

  void addPort(std::unique_ptr<ElementPort>&& port);

private:
  std::vector<std::unique_ptr<ElementPort>> m_ports;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTPORT_H
