#ifndef ELEMENTCONNECTION_H
#define ELEMENTCONNECTION_H

#include <limits>
#include <vector>
#include <string>

namespace PowerLab {
namespace ModelDesign {

using ConnectionId = size_t;

static constexpr ConnectionId UNCONNECTED = std::numeric_limits<size_t>::max();

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

private:
  std::vector<ElementPort*> m_connectedPorts;
  const ConnectionId m_id;
  std::string m_userName;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTCONNECTION_H
