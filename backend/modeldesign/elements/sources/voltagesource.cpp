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

} // namespace ModelDesign
} // namespace PowerLab
