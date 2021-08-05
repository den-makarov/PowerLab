#include <sstream>
#include <cassert>

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

  m_parameters.addParameter(std::string(AC_AMPLITUDE), std::move(amplitude));
  m_parameters.addParameter(std::string(DC_BIAS), std::move(bias));
  m_parameters.addParameter(ParameterType::FREQUENCY, std::move(frequency));
  m_parameters.addParameter(ParameterType::PHASE, std::move(phase));
}

std::string SinusoidalWaveForm::getModel() const {
  std::ostringstream model;
  model << "SIN(";

  auto dcBias = m_parameters.getParameter(std::string(DC_BIAS));
  if(dcBias) {
    model << dcBias->getValue<double>();
  } else {
    assert(false && "MANDATORY PARAMETER IS LOST: DC BIAS");
    model << "0.0 ";
  }

  auto ampl = m_parameters.getParameter(std::string(AC_AMPLITUDE));
  if(ampl) {
    model << ampl->getValue<double>();
  } else {
    assert(false && "MANDATORY PARAMETER IS LOST: AMPLITUDE");
    model << "0.0 ";
  }

  auto frequency = m_parameters.getParameter(ParameterType::FREQUENCY);
  if(frequency) {
    model << frequency->getValue<double>();
  } else {
    assert(false && "MANDATORY PARAMETER IS LOST: FREQUENCY");
    model << "0.0 ";
  }

  auto delay = m_parameters.getParameter(ParameterType::TIME);
  if(delay) {
    model << delay->getValue<double>();
  } else {
    model << "0.0 ";
  }

  auto dumping = m_parameters.getParameter(std::string(DUMPING_FACTOR));
  if(dumping) {
    model << dumping->getValue<double>();
  } else {
    model << "0.0 ";
  }

  auto phase = m_parameters.getParameter(ParameterType::PHASE);
  if(phase) {
    model << phase->getValue<double>();
  } else {
    assert(false && "MANDATORY PARAMETER IS LOST: PHASE");
    model << "0.0";
  }

  model << ")";
  return model.str();
}

} // namespace ModelDesign
} // namespace PowerLab
