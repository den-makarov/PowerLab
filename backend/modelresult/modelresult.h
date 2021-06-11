#ifndef MODELRESULT_H
#define MODELRESULT_H

#include <vector>
#include <string>
#include <utility>
#include <functional>

#include "modelresultmeta.h"

namespace Model {

class ModelResultValidator;

class ModelResult {
public:
  using DataPoint = double;
  using SignalName = std::string;
  using SignalDataPoints = std::vector<DataPoint>;
  using MetaDataLoadCB = std::function<void(const ModelResultMeta::Data*, const std::string&)>;

  ModelResult();
  ~ModelResult();

  size_t getVariablesNumber() const;
  size_t getPointsNumber() const;
  void addSignalDataPoint(const SignalName& signalName, DataPoint point);
  void addSignalDataPoints(const SignalName& signalName, const SignalDataPoints& points);
  template<typename DataIterator>
  void addSignalDataPoints(const SignalName& signalName,
                           DataIterator begin,
                           DataIterator end);

  SignalDataPoints getSignalDataPoints(const SignalName& name) const;
  std::vector<SignalName> getAllSignalNames() const;
  void openFile(const std::string& filename);
  void setupMetaDataLoadCB(MetaDataLoadCB cb);

private:
  struct Signal {
    SignalDataPoints points;
    ModelResultMeta::SignalDescriptor signal;
  };

  ModelResultValidator* m_validator;
  std::map<SignalName, Signal> m_signals;
  MetaDataLoadCB m_metaDataLoadCB = defaultMetaDataLoadSignal;
  const ModelResultMeta* m_meta = nullptr;

  static constexpr size_t MAX_VARIABLES_NUMBER = 25;
  static constexpr size_t MAX_POINTS_NUMBER = 1'000'000;

  static void defaultMetaDataLoadSignal(const ModelResultMeta::Data* data,
                                        const std::string& msg);

  void extractSignalsDataPoints(const std::string& filename);
};

} // namespace model
#endif // MODELRESULT_H
