#ifndef SOURCE_H
#define SOURCE_H

#include <memory>

#include "modeldesign/abstractelement.h"
#include "waveformsource.h"

namespace PowerLab {
namespace ModelDesign {

class Source : public CircuitElement {
public:
  enum class Type {
    VOLTAGE,
    CURRENT
  };

  explicit Source(const ElementName& name, std::unique_ptr<WaveFormSource>&& waveform);
  virtual ~Source() = default;
  virtual Type getSourceType() const = 0;

  const WaveFormSource& getWaveForm() const;
  WaveFormSource& getWaveForm();
private:
  std::unique_ptr<WaveFormSource> m_waveform;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // SOURCE_H
