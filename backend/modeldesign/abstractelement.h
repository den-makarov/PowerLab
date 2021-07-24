#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H

#include <vector>
#include <string>
#include <memory>

#include "elementport.h"
#include "elementparameter.h"

namespace PowerLab {
namespace Model {

class AbstractElement {
public:
  using ElementName = std::string;

  AbstractElement(const ElementName& name);
  ~AbstractElement();

  const ElementName& getName() const;

  void addPort(std::unique_ptr<ElementPort>&& port);
  void addChild(std::unique_ptr<AbstractElement>&& child);
  void addParameter(std::unique_ptr<ElementParameter>&& parameter);

private:
  int x;
  int y;
  ElementName m_name;
  std::vector<std::unique_ptr<ElementPort>> m_ports;
  std::vector<std::unique_ptr<AbstractElement>> m_children;
  std::vector<std::unique_ptr<ElementParameter>> m_parameters;
};

} // namespace Model
} // namespace PowerLab

#endif // ABSTRACTELEMENT_H
