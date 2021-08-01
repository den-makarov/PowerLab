#ifndef SINUSOIDALWAVEFORM_H
#define SINUSOIDALWAVEFORM_H

// SIN(VO VA FREQ TD THETA PHASE)
// VO - constant offset
// VA - amplitude
// FREQ - frequence [Hz]
// TD - time delay [sec]
// THETA - Damping factor [1/sec]
// PHASE - phase shift [degrees]

#include "waveformsource.h"

namespace PowerLab {
namespace ModelDesign {

class SinusoidalWaveForm : public WaveFormSource {
public:
  SinusoidalWaveForm();
  virtual ~SinusoidalWaveForm() override = default;

  virtual std::string getModel() const override;
};


} // namespace ModelDesign
} // namespace PowerLab

#endif // SINUSOIDALWAVEFORM_H
