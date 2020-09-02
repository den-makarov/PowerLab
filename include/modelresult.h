#ifndef MODELRESULT_H
#define MODELRESULT_H

#include <vector>
#include <string>
#include <utility>
#include <QObject>

class ModelResult : public QObject
{
  Q_OBJECT
public:
  explicit ModelResult(size_t variables, size_t points, QObject *parent = nullptr);

  size_t getVariablesNumber() const;
  size_t getPointsNumber() const;

private:
  std::vector<std::vector<double>> m_data;
  std::vector<std::pair<std::string, std::string>> m_signals;
};

#endif // MODELRESULT_H
