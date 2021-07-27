#ifndef ELEMENTPORT_H
#define ELEMENTPORT_H

#include <set>

#include "elementconnection.h"

namespace PowerLab {
namespace ModelDesign {

class AbstractElement;

class ElementPort {
public:
  ElementPort(const AbstractElement& owner);

  void connect(ConnectionId connection);
  void disconnect();
  bool isConnected() const;

private:
  ConnectionId m_connection;
  const AbstractElement& m_owner;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTPORT_H
