#include "voltagesource.h"

namespace PowerLab {
namespace ModelDesign {

VoltageSource::VoltageSource(const ElementName& name, std::unique_ptr<WaveFormSource>&& waveform)
  : Source(name, std::move(waveform))
{
}

Source::Type VoltageSource::getSourceType() const {
  return Type::VOLTAGE;
}

} // namespace ModelDesign
} // namespace PowerLab
