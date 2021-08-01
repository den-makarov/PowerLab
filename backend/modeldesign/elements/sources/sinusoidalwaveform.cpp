#include "sinusoidalwaveform.h"
#include "modeldesign/parameters/quantity.h"
#include "modeldesign/parameters/frequency.h"
#include "modeldesign/parameters/phase.h"

namespace PowerLab {
namespace ModelDesign {

SinusoidalWaveForm::SinusoidalWaveForm()
  : WaveFormSource(SignalType::SINUSOIDAL)
{
  auto amplitude = std::make_unique<Quantity>(1.0);
  auto bias = std::make_unique<Quantity>(0.0);
  auto frequency = std::make_unique<Frequency>(50.0);
  auto phase = std::make_unique<Phase>(0.0);

  m_parameters.addParameter("amplitude", std::move(amplitude));
  m_parameters.addParameter("bias", std::move(bias));
  m_parameters.addParameter(ParameterType::FREQUENCY, std::move(frequency));
  m_parameters.addParameter(ParameterType::PHASE, std::move(phase));
}

std::string SinusoidalWaveForm::getModel() const {
  return "";
}

} // namespace ModelDesign
} // namespace PowerLab
