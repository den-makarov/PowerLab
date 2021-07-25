#ifndef WAVEFORMSOURCE_H
#define WAVEFORMSOURCE_H

namespace PowerLab {
namespace ModelDesign {

class WaveFormSource {
public:
  enum class Type {
    NO_WAVEFORM, // Used for measurement purpose
    DIRECT_CURRENT,
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

  WaveFormSource();
  virtual ~WaveFormSource() = default;

  virtual Type getWaveFormType() = 0;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // WAVEFORMSOURCE_H
