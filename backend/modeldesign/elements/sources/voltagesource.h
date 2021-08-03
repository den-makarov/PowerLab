#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include "source.h"

namespace PowerLab {
namespace ModelDesign {

class VoltageSource : public Source {
public:
  virtual ~VoltageSource() override = default;
protected:
  VoltageSource(const ElementName& name, std::unique_ptr<WaveFormSource>&& waveform);
private:
};

class AcVoltageSource : public VoltageSource {
public:
  AcVoltageSource(const ElementName& name);
  virtual ~AcVoltageSource() override = default;
};

} // namespace ModelDesign
} // namespace PowerLab

#endif // VOLTAGESOURCE_H
