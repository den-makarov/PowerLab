#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "elementport.h"
#include "elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class AbstractElement {
public:
  using ElementName = std::string;
  using ParameterName = std::string;

  explicit AbstractElement(const ElementName& name);

  const ElementName& getName() const;
  void updateName(const ElementName& name);

  void addPort(std::unique_ptr<ElementPort>&& port);
  void addChild(std::unique_ptr<AbstractElement>&& child);
  void addParameter(const ParameterName& name, std::unique_ptr<ElementParameter>&& parameter);

private:
  ElementName m_name;
  std::vector<std::unique_ptr<ElementPort>> m_ports;
  std::vector<std::unique_ptr<AbstractElement>> m_children;
  std::map<ParameterName, std::unique_ptr<ElementParameter>> m_parameters;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ABSTRACTELEMENT_H
