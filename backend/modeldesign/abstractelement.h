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

  const ElementName& getName() const;
  void updateName(const ElementName& name);

  void addChild(std::unique_ptr<CircuitElement>&& child);
  std::vector<const ElementParameter*> getAllParameters() const;

  std::vector<const ElementPort*> getAllPorts() const;
  std::vector<ElementPort*> getAllPorts();

protected:
  explicit CircuitElement(const ElementName& name);

  void addPort(std::unique_ptr<ElementPort>&& port);

  ElementParameterMap m_parameters;

private:
  ElementName m_name;
  std::vector<std::unique_ptr<ElementPort>> m_ports;
  std::vector<std::unique_ptr<CircuitElement>> m_children;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ABSTRACTELEMENT_H
