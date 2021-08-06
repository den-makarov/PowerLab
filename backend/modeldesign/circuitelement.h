#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H

#include <vector>
#include <string>
#include <memory>

#include "elementport.h"
#include "elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class CircuitElement {
public:
  using ElementName = std::string;
  virtual ~CircuitElement();

  const ElementName& getName() const;
  void updateName(const ElementName& name);

  void addChild(std::unique_ptr<CircuitElement>&& child);
  std::vector<const ElementParameter*> getAllParameters() const;

  std::vector<ElementPortCRef> getAllPorts() const;
  std::vector<ElementPortRef> getAllPorts();

  std::vector<ElementPortCRef> getPortsOfType(PortType type) const;
  std::vector<ElementPortRef> getPortsOfType(PortType type);

  virtual std::string getModel() const {return "";}

protected:
  explicit CircuitElement(const ElementName& name);

  void addPort(std::unique_ptr<ElementPort>&& port);

  ElementParameterMap m_parameters;

private:
  ElementName m_name;
  ElementPortMap m_ports;
  std::vector<std::unique_ptr<CircuitElement>> m_children;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ABSTRACTELEMENT_H
