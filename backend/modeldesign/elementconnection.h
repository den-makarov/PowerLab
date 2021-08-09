#ifndef ELEMENTCONNECTION_H
#define ELEMENTCONNECTION_H

#include <limits>
#include <vector>
#include <string>
#include <memory>

namespace PowerLab {
namespace ModelDesign {

class ElementPort;

class ElementConnection;
using Connection = std::shared_ptr<ElementConnection>;

class ElementConnection {
public:
  static Connection createConnection();

  explicit ElementConnection();
  ~ElementConnection();

  void setUserName(const std::string& name);
  const std::string& getUserName() const;

  void connectPort(ElementPort& port);
  void disconnectPort(ElementPort& port);
  bool isConnectedPort(const ElementPort& port) const;

  std::string getModel() const;

  std::string str() const;

private:
  using ConnectionId = int32_t;
  static ConnectionId globalId;

  const ConnectionId m_id;
  std::vector<ElementPort*> m_connectedPorts;
  std::string m_userName;
};


} // namespace ModelDesign
} // namespace PowerLab

#endif // ELEMENTCONNECTION_H
