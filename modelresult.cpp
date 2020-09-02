#include <logger.h>
#include "modelresult.h"

ModelResult::ModelResult(size_t variables, size_t points, QObject *parent) : QObject(parent)
{
  if(variables <= 1) {
    Logger::instance()->debug(this->metaObject()->className()) << "invalid size of variables"
                                                               << variables;

    variables = 1;
  }

  if(points <= 1) {
    qWarning() << "[" << this->metaObject()->className() << "]"
               << "number of points too small"
               << points;
  }

  m_data = std::vector<std::vector<double>>(variables);
  for(auto& item : m_data) {
    item = std::vector<double>(points, 0.0);
  }

  m_signals = std::vector<std::pair<std::string, std::string>>(variables);
  for(auto& item : m_signals) {
    item = std::make_pair<std::string, std::string>("NO_NAME", "NO_UNIT");
  }
}

size_t ModelResult::getVariablesNumber() const {
  return m_data.size();
}

size_t ModelResult::getPointsNumber() const {
  return m_data[0].size();
}
