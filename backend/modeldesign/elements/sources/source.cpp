#include "source.h"

namespace PowerLab {
namespace ModelDesign {

Source::Source(const ElementName& name, std::unique_ptr<WaveFormSource>&& waveform)
  : CircuitElement(name)
  , m_waveform(std::move(waveform))
{
}

const WaveFormSource& Source::getWaveForm() const {
  return *m_waveform;
}

WaveFormSource& Source::getWaveForm() {
  return *m_waveform;
}

} // namespace ModelDesign
} // namespace PowerLab
