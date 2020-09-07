#ifndef MODELRESULT_H
#define MODELRESULT_H

#include <vector>
#include <string>
#include <utility>
#include <QObject>

#define E_MODEL_RESULT_STRICT_CHECK

class ModelResult : public QObject
{
  Q_OBJECT
public:
  using DataPoints = std::vector<double>;
  using DataNames = std::pair<std::string, std::string>;
  explicit ModelResult(size_t variables, size_t points, QObject *parent = nullptr);

  size_t getVariablesNumber() const;
  size_t getPointsNumber() const;
  void addDataPoint(size_t var, double point);
  void addDataPoint(size_t var, const DataPoints& data);
  void setDataNames(size_t var, DataNames& names);

private:
  std::vector<DataPoints> m_data;
  std::vector<DataNames> m_signals;
};

#endif // MODELRESULT_H
