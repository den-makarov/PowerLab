#ifndef ELEMENTCONNECTION_H
#define ELEMENTCONNECTION_H

#include <vector>

namespace PowerLab {
namespace ModelDesign {

using ConnectionId = size_t;

class ElementPort;

class ElementConnection {
public:
  explicit ElementConnection(ConnectionId id);
  ~ElementConnection();

  void connectPort(ElementPort* port);
  void disconnectPort(ElementPort* port);
  bool isConnectedPort(const ElementPort* port) const;

private:
  std::vector<ElementPort*> m_connectedPorts;
  const ConnectionId m_id;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTCONNECTION_H
