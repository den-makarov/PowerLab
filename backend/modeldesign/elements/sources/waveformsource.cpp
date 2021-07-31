#include "waveformsource.h"

namespace PowerLab {
namespace ModelDesign {

WaveFormSource::WaveFormSource(SignalType form)
  : m_signalType(form)
{
}

std::vector<const ElementParameter*> WaveFormSource::getAllParameters() const {
  return m_parameters.getAllParameters();
}

SignalType WaveFormSource::getSignalType() const {
  return m_signalType;
}

} // namespace ModelDesign
} // namespace PowerLab
