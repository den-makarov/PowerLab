#ifndef SWITCHSTATE_H
#define SWITCHSTATE_H

#include <string>
#include <type_traits>

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

class SwitchState {
public:
  enum class State {
    ON,
    OFF
  };

  explicit SwitchState(bool state = false)
    : m_state(state)
  {}

  explicit SwitchState(std::string state = "OFF")
    : m_state(state == "ON")
  {}

  explicit SwitchState(int state = 0)
    : SwitchState(state >= 1)
  {}

  explicit SwitchState(State state = State::OFF)
    : SwitchState(state != State::OFF)
  {}

  std::string str() const {
    return m_state ? "ON" : "OFF";
  }

  template<typename Integer, std::enable_if_t<std::is_same_v<Integer, int>, bool> = true>
  Integer state() const {
    return m_state ? 1 : 0;
  }

  template<typename Boolean, std::enable_if_t<std::is_same_v<Boolean, bool>, bool> = true>
  Boolean state() const {
    return m_state;
  }

  State state() const {
    return m_state ? State::ON : State::OFF;
  }

private:
  const bool m_state;
};

class SwitchStatus : public StateElementParameter {
public:
  SwitchStatus(SwitchState state);
  virtual ~SwitchStatus() override = default;

  virtual ParameterType getType() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // SWITCHSTATE_H
