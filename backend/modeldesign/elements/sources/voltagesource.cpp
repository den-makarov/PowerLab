#include <sstream>

#include "voltagesource.h"
#include "sinusoidalwaveform.h"

namespace PowerLab {
namespace ModelDesign {

VoltageSource::VoltageSource(const ElementName& name, std::unique_ptr<WaveFormSource>&& waveform)
  : Source(name, Type::VOLTAGE, std::move(waveform))
{
}

AcVoltageSource::AcVoltageSource(const ElementName& name)
  : VoltageSource(name, std::make_unique<SinusoidalWaveForm>())
{

}

std::string AcVoltageSource::getModel() const {
  std::ostringstream model;

  auto& name = getName();
  if(name.empty()) {
    // ERROR
    return "";
  }

  if(name.front() != 'V') {
    // ERROR
    return "";
  }

  model << name;

  auto inPorts = getPortsOfType(PortType::POWER_IN);
  auto outPorts = getPortsOfType(PortType::POWER_OUT);

  if(inPorts.size() != 1 || outPorts.size() != 1) {
    // ERROR
    return "";
  }

  model << " ";
  getConnectionModel(model, &inPorts.front().get());

  model << " ";
  getConnectionModel(model, &outPorts.front().get());

  model << " " << getWaveForm().getModel();

  return model.str();
}

} // namespace ModelDesign
} // namespace PowerLab
