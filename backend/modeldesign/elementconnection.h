#ifndef ELEMENTCONNECTION_H
#define ELEMENTCONNECTION_H

#include <limits>
#include <vector>
#include <string>

namespace PowerLab {
namespace ModelDesign {

using ConnectionId = size_t;

static constexpr ConnectionId UNCONNECTED = std::numeric_limits<size_t>::max();
static constexpr ConnectionId INVALID_CONNECTION = std::numeric_limits<size_t>::max();

class ElementPort;

class ElementConnection {
public:
  explicit ElementConnection(ConnectionId id);
  ~ElementConnection();

  void setUserName(const std::string& name);
  const std::string& getUserName() const;

  void connectPort(ElementPort* port);
  void disconnectPort(ElementPort* port);
  bool isConnectedPort(const ElementPort* port) const;

  std::string getModel() const;

  std::string str() const;

private:
  std::vector<ElementPort*> m_connectedPorts;
  const ConnectionId m_id;
  std::string m_userName;
};

class Connection {
public:
  explicit Connection(ConnectionId id = INVALID_CONNECTION);

  static bool isValid(ConnectionId id);

  void setUserName(const std::string& name);
  std::string getUserName() const;

  void connectPort(ElementPort* port);
  void disconnectPort(ElementPort* port);
  bool isConnectedPort(const ElementPort* port) const;

  std::string getModel() const;
  std::string str() const;

private:
  bool isExist() const;

  ElementConnection* getConnection() const;
  const ConnectionId m_id;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTCONNECTION_H
