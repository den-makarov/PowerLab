#ifndef WAVEFORMSOURCE_H
#define WAVEFORMSOURCE_H

#include <string>

#include "modeldesign/elementparameter.h"

namespace PowerLab {
namespace ModelDesign {

enum class SignalType {
  UNDEFINED, // Used for measurement purpose
  CONSTANT,
  PULSE,
  EXPONENTIAL,
  SINUSOIDAL,
  PIECE_WISE,
  SINGLE_FREQUENCE_MODULATED,
  AMLITUDE_MODULATED,
  TRANSIENT_NOISE,
  RANDOM,
  EXTERNAL_DATA
};

static constexpr SignalType CURRENT_MEASUREMENT = SignalType::UNDEFINED;

class WaveFormSource {
public:
  virtual ~WaveFormSource() = default;

  virtual std::string getModel() const = 0;

  std::vector<const ElementParameter*> getAllParameters() const;

  SignalType getSignalType() const;

protected:
  explicit WaveFormSource(SignalType form = SignalType::UNDEFINED);

  ElementParameterMap m_parameters;

private:
  const SignalType m_signalType;
};

class EmptyWaveForm : WaveFormSource {
public:
  EmptyWaveForm();
  virtual ~EmptyWaveForm() override = default;

  virtual std::string getModel() const override;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // WAVEFORMSOURCE_H
