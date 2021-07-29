#ifndef ELEMENTPORT_H
#define ELEMENTPORT_H

#include "elementconnection.h"

namespace PowerLab {
namespace ModelDesign {

class CircuitElement;

class ElementPort {
public:
  ElementPort(const CircuitElement& owner);

  void connect(ConnectionId connection);
  void disconnect();
  bool isConnected() const;

private:
  ConnectionId m_connection = UNCONNECTED;
  const CircuitElement& m_owner;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTPORT_H
