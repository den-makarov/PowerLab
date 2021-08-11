#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "elementport.h"
#include "elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class CircuitElement;
using Element = std::shared_ptr<CircuitElement>;

class CircuitElement {
public:
  using ElementName = std::string;
  virtual ~CircuitElement();

  const ElementName& getName() const;
  void updateName(const ElementName& name);

  void addChild(std::unique_ptr<CircuitElement>&& child);
  std::vector<const ElementParameter*> getAllParameters() const;

  std::vector<CPort> getAllPorts() const;
  std::vector<Port> getAllPorts();

  std::vector<CPort> getPortsOfType(PortType type) const;
  std::vector<Port> getPortsOfType(PortType type);

  virtual std::string getModel() const {return "";}

protected:
  explicit CircuitElement(const ElementName& name);

  void addPort(Port port);
  std::ostream& getConnectionModel(std::ostream&, CPort port) const;

  ElementParameterMap m_parameters;

private:
  ElementName m_name;
  ElementPortMap m_ports;
  std::vector<std::unique_ptr<CircuitElement>> m_children;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ABSTRACTELEMENT_H
