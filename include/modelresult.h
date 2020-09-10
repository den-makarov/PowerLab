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

  const DataPoints& getDataPoints(size_t var) const;
  const DataNames& getDataNames(size_t var) const;

private:
  std::vector<DataPoints> m_data;
  std::vector<DataNames> m_signals;
  static DataPoints dummyPoints;
  static DataNames dummyNames;

  static constexpr size_t MAX_VARIABLES_NUMBER = 25;
  static constexpr size_t MAX_POINTS_NUMBER = 1'000'000;
};

#endif // MODELRESULT_H
