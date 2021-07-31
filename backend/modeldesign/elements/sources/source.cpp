#include "source.h"

namespace {

std::string sourceTypeToStr(PowerLab::ModelDesign::Source::Type type) {
  using sType = PowerLab::ModelDesign::Source::Type;
  switch(type) {
  case sType::CURRENT: return "current";
  case sType::VOLTAGE: return "voltage";
  }
}

}

namespace PowerLab {
namespace ModelDesign {

Source::Source(const ElementName& name, Type type, std::unique_ptr<WaveFormSource>&& waveform)
  : CircuitElement(name)
  , m_waveform(std::move(waveform))
  , m_type(type)
{
}

const WaveFormSource& Source::getWaveForm() const {
  return *m_waveform;
}

WaveFormSource& Source::getWaveForm() {
  return *m_waveform;
}

Source::Type Source::getSourceType() const {
  return m_type;
}

std::string Source::str() const {
  std::string str = " source";
  return sourceTypeToStr(m_type) + str;
}

} // namespace ModelDesign
} // namespace PowerLab
