#include "model.h"
#include "modeldesign/elements/basic/resistor.h"
#include "modeldesign/elements/basic/capacitor.h"
#include "modeldesign/elements/basic/inductor.h"
#include "modeldesign/elements/basic/switch.h"
#include "modeldesign/elements/sources/voltagesource.h"
#include "modeldesign/parameters/switchstate.h"
#include "modeldesign/elementconnectionmanager.h"
#include "modeldesign/elementconnection.h"
#include "logger.h"

namespace PowerLab {
namespace ModelDesign {

Model::Model(const std::string& name)
  : m_name(name)
{
  Element R1(new ModelDesign::Resistor("R1"));
  Element L1(new ModelDesign::Inductor("L1"));
  Element C1(new ModelDesign::Capacitor("C1"));
  Element VA1(new ModelDesign::AcVoltageSource("VA1"));
  addElement(R1);
  addElement(L1);
  addElement(C1);
  addElement(VA1);

  ModelDesign::Connection ground = ModelDesign::ElementConnection::createConnection();
  addConnection(ground);
  m_elements["VA1"]->getAllPorts()[1]->connect(ground);
  m_elements["R1"]->getAllPorts()[1]->connect(ground);
  m_elements["C1"]->getAllPorts()[1]->connect(ground);

  ModelDesign::Connection input = ModelDesign::ElementConnection::createConnection();
  addConnection(input);
  m_elements["VA1"]->getAllPorts()[0]->connect(input);
  m_elements["L1"]->getAllPorts()[0]->connect(input);

  ModelDesign::Connection output = ModelDesign::ElementConnection::createConnection();
  addConnection(output);
  m_elements["L1"]->getAllPorts()[1]->connect(output);
  m_elements["R1"]->getAllPorts()[0]->connect(output);
  m_elements["C1"]->getAllPorts()[0]->connect(output);

  for(auto& item : m_connections) {
    Logger::log(Logger::Message::DEBUG_MSG, item->str());
  }

  m_elements["L1"]->getAllPorts()[1]->disconnect();
  input->disconnectPort(*(m_elements["L1"]->getAllPorts()[0]));
  for(auto& [name, item] : m_elements) {
    auto model = item->getModel();
    Logger::log(Logger::Message::DEBUG_MSG, model);
  }
}

std::vector<Connection> Model::getConnections() {
  std::vector<Connection> result(m_connections.begin(), m_connections.end());
  return result;
}

void Model::addConnection(Connection connection) {
  m_connections.insert(connection);
}

std::vector<Element> Model::getElements() {
  std::vector<Element> result;
  for(auto& [name, element] : m_elements) {
    result.push_back(element);
  }
  return result;
}

void Model::addElement(Element element) {
  m_elements.emplace(element->getName(), element);
}


} // namespace ModelDesign
} // namespace PowerLab
