#include "elementport.h"
#include "elementconnectionmanager.h"

namespace PowerLab {
namespace ModelDesign {

ElementPort::ElementPort(const CircuitElement& owner)
  : m_owner(owner)
{

}

void ElementPort::connect(ConnectionId connection) {
  m_connection = connection;
}

void ElementPort::disconnect() {
  m_connection = UNCONNECTED;
}

bool ElementPort::isConnected() const {
  return m_connection != UNCONNECTED;
}

} // namespace ModelDesign
} // namespace PowerLab
