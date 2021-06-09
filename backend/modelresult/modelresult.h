#ifndef MODELRESULT_H
#define MODELRESULT_H

#include <vector>
#include <string>
#include <utility>
#include <functional>

#include "modelresultmeta.h"

class ModelResultValidator;

class ModelResult {
public:
  using DataPoints = std::vector<double>;
  using DataNames = std::pair<std::string, std::string>;
  using SignalNames = std::vector<ModelResultMeta::SignalDescriptor>;
  using MetaDataLoadCB = std::function<void(const ModelResultMeta::Data*, const std::string&)>;

  ModelResult();
  ~ModelResult();

  size_t getVariablesNumber() const;
  size_t getPointsNumber() const;
  void addDataPoint(size_t var, double point);
  void addDataPoint(size_t var, const DataPoints& data);

  const DataPoints& getDataPoints(size_t var) const;
  const SignalNames* getSignalNames() const;
  void openFile(const std::string& filename);
  void setupMetaDataLoadCB(MetaDataLoadCB cb);

private:
  ModelResultValidator* m_validator;
  std::vector<DataPoints> m_data;
  std::vector<DataNames> m_signals;
  MetaDataLoadCB m_metaDataLoadCB = defaultMetaDataLoadSignal;
  const ModelResultMeta* m_meta = nullptr;

  static DataPoints dummyPoints;
  static DataNames dummyNames;
  static constexpr size_t MAX_VARIABLES_NUMBER = 25;
  static constexpr size_t MAX_POINTS_NUMBER = 1'000'000;

  void init(size_t variables, size_t points);
  static void defaultMetaDataLoadSignal(const ModelResultMeta::Data* data,
                                        const std::string& msg);
};

#endif // MODELRESULT_H
