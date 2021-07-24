#ifndef ELEMENTPORT_H
#define ELEMENTPORT_H

#include <set>

#include "elementconnection.h"

namespace PowerLab {
namespace Model {

class AbstractElement;

class ElementPort {
public:
  ElementPort(const AbstractElement& owner);

  void connect(ConnectionId connection);
  void disconnect(ConnectionId connection);
  bool isConnected(ConnectionId connection) const;

private:
  std::set<ConnectionId> m_connections;
  const AbstractElement& m_owner;
};

} // namespace Model
} // namespace PowerLab

#endif // ELEMENTPORT_H
