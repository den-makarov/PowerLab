#ifndef MODELRESULT_H
#define MODELRESULT_H

#include <vector>
#include <string>
#include <utility>
#include <QObject>

#define E_MODEL_RESULT_STRICT_CHECK

#include "modelresultmeta.h"

class ModelResultValidator;

class ModelResult : public QObject
{
  Q_OBJECT
public:
  using DataPoints = std::vector<double>;
  using DataNames = std::pair<std::string, std::string>;
  ModelResult(QObject *parent = nullptr);
  ~ModelResult();

  size_t getVariablesNumber() const;
  size_t getPointsNumber() const;
  void addDataPoint(size_t var, double point);
  void addDataPoint(size_t var, const DataPoints& data);

  const DataPoints& getDataPoints(size_t var) const;
  const std::vector<ModelResultMeta::SignalDescriptor>* getSignalNames() const;

public slots:
  void openFile();

signals:
  void metaDataLoaded(const ModelResultMeta::Data* data, QString msg = "");

private:
  ModelResultValidator* m_validator;
  std::vector<DataPoints> m_data;
  std::vector<DataNames> m_signals;
  const ModelResultMeta* m_meta = nullptr;
  static DataPoints dummyPoints;
  static DataNames dummyNames;

  static constexpr size_t MAX_VARIABLES_NUMBER = 25;
  static constexpr size_t MAX_POINTS_NUMBER = 1'000'000;

  void init(size_t variables, size_t points);
};

#endif // MODELRESULT_H
