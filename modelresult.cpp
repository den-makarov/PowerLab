#include <logger.h>
#include "modelresult.h"

ModelResult::ModelResult(size_t variables, size_t points, QObject *parent) : QObject(parent)
{
  if(variables == 0) {
    E_WARNING(this) << "invalid size of variables"
                    << variables;

    variables = 1;
  }

  if(points <= 1) {
    E_WARNING(this) << "number of points too small"
                    << points;
    points = 0;
  }

  m_data = std::vector<DataPoints>(variables);
  for(auto& item : m_data) {
    item.reserve(points);
  }

  m_signals = std::vector<DataNames>(variables);
  for(auto& item : m_signals) {
    item = std::make_pair<std::string, std::string>("NO_NAME", "NO_UNIT");
  }
}

size_t ModelResult::getVariablesNumber() const {
  return m_data.size();
}

size_t ModelResult::getPointsNumber() const {
  if(m_data.empty()) {
    E_CRITICAL(this) << "Invalid container state";
    return 0;
  }

  return m_data[0].size();
}

void ModelResult::addDataPoint(size_t var, double point) {
#ifdef E_MODEL_RESULT_STRICT_CHECK
  if(m_data.empty()) {
    E_CRITICAL(this) << "Invalid container";
    return;
  }
#endif

  if(var >= m_data[0].size()) {
    E_CRITICAL(this) << "Invalid identifier";
    return;
  }

  m_data[var].push_back(point);
}

void ModelResult::setDataNames(size_t var, DataNames& names) {
  if(var >= m_signals.size()) {
    E_CRITICAL(this) << "Invalid identifier";
    return;
  }

  m_signals[var] = names;
}
