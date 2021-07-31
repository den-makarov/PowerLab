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

  virtual ~Source() = default;
  Type getSourceType() const;

  const WaveFormSource& getWaveForm() const;
  WaveFormSource& getWaveForm();

  virtual std::string str() const;
protected:
  explicit Source(const ElementName& name, Type type, std::unique_ptr<WaveFormSource>&& waveform);

private:
  std::unique_ptr<WaveFormSource> m_waveform;
  const Type m_type;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // SOURCE_H
