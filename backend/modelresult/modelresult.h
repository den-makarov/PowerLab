#ifndef MODELRESULT_H
#define MODELRESULT_H

#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <memory>

#include "modelresultmeta.h"

namespace Model {

class ModelResultValidator;

class ModelResult {
public:
  using DataPoint = double;
  using SignalName = std::string;
  using SignalDataPoints = std::vector<DataPoint>;
  using MetaDataLoadCB = std::function<void(bool, const std::string&)>;

  ModelResult();

  std::string getModelTitle() const;
  size_t getVariablesNumber() const;
  size_t getPointsNumber() const;
  void addSignalDataPoint(const SignalName& signalName, DataPoint point);
  void addSignalDataPoints(const SignalName& signalName, const SignalDataPoints& points);
  template<typename DataIterator>
  void addSignalDataPoints(const SignalName& signalName,
                           DataIterator begin,
                           DataIterator end);

  std::string getSignalUnitsSISymbol(const std::string& signalName) const;
  SignalDataPoints getSignalDataPoints(const SignalName& name) const;
  std::vector<SignalName> getAllSignalNames() const;
  SignalName getReferenceSignalName() const;
  void openFile(const std::string& filename);
  void setupMetaDataLoadCB(MetaDataLoadCB cb);

private:
  struct Signal {
    SignalDataPoints points;
    ModelResultMeta::SignalDescriptor signal;
    bool isReference;
  };

  std::unique_ptr<ModelResultValidator> m_validator;
  std::map<SignalName, Signal> m_signals;
  MetaDataLoadCB m_metaDataLoadCB = defaultMetaDataLoadSignal;

  static constexpr size_t MAX_VARIABLES_NUMBER = 25;
  static constexpr size_t MAX_POINTS_NUMBER = 1'000'000;

  static void defaultMetaDataLoadSignal(bool parsingResult,
                                        const std::string& msg);

  void extractSignalsDataPoints(const std::string& filename);
};

} // namespace model
#endif // MODELRESULT_H
