#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include "source.h"

namespace PowerLab {
namespace ModelDesign {

class VoltageSource : public Source {
public:
  VoltageSource(const ElementName& name, std::unique_ptr<WaveFormSource>&& waveform);
  virtual ~VoltageSource() override = default;
  virtual Type getSourceType() const override;
private:
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // VOLTAGESOURCE_H
