#include "voltagesource.h"

namespace PowerLab {
namespace ModelDesign {

VoltageSource::VoltageSource(const ElementName& name, std::unique_ptr<WaveFormSource>&& waveform)
  : Source(name, Type::VOLTAGE, std::move(waveform))
{
}

} // namespace ModelDesign
} // namespace PowerLab
